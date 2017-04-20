#include "utility.hh"

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
    return this->operator()(domain.types.at(type_name).get_type_name(),
                            target_type);
}

} // namespace pddl_parser
