#include <pddl_parser/domain.hh>
#include <pddl_parser/instance.hh>
#include <pddl_parser/utility.hh>

namespace pddl_parser {

ObjectFetcher::ObjectFetcher(Domain const &domain, Instance const &instance)
    : domain(domain),
      instance(instance) {
}

TypedName const & ObjectFetcher::operator()(
    std::string const &object_name) const {
    auto const &it = instance.objects.find(object_name);
    if (it == instance.objects.end()) {
        return domain.constants.at(object_name);
    }
    return it->second;
}

TypeChecker::TypeChecker(Domain const &domain)
    : domain(domain) {
}

bool TypeChecker::operator()(std::string const &type_name,
                             std::string const &target_type) const {
    if (type_name == target_type) {
        return true;
    }
    else if (type_name == "object") {
        return false;
    }
    return this->operator()(domain.types.at(type_name).type_name, target_type);
}

TypeMembersFetcher::TypeMembersFetcher(Domain const &domain,
                                       Instance const &instance)
    : domain(domain),
      instance(instance),
      type_checker(domain) {
}

std::deque<std::string> TypeMembersFetcher::operator()(
    std::string const &type_name) const {

    std::deque<std::string> output;

    for (auto const &pair : domain.constants) {
        if (type_checker(pair.second.type_name, type_name)) {
            output.emplace_back(pair.second.name);
        }
    }
    for (auto const &pair : instance.objects) {
        if (type_checker(pair.second.type_name, type_name)) {
            output.emplace_back(pair.second.name);
        }
    }

    return output;

}

} // namespace pddl_parser
