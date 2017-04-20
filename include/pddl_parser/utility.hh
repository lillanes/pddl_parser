#ifndef PDDL_PARSER_UTILITY_HH
#define PDDL_PARSER_UTILITY_HH

#include "domain.hh"
#include "instance.hh"
#include "typed_name.hh"

namespace pddl_parser {

class ObjectFetcher {
    Domain const &domain;
    Instance const &instance;
public:
    ObjectFetcher(Domain const &domain, Instance const &instance);
    TypedName const & operator()(std::string const &object_name) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_UTILITY_HH
