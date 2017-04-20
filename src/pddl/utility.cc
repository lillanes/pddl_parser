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

} // namespace pddl_parser
