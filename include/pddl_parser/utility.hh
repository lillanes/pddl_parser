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

class TypeChecker {
    Domain const &domain;
public:
    TypeChecker(Domain const &domain);
    bool operator()(std::string const &type_name,
                    std::string const &target_type) const;
};

class TypeMembersFetcher {
    Domain const &domain;
    Instance const &instance;
    TypeChecker type_checker;
public:
    TypeMembersFetcher(Domain const &domain, Instance const &instance);
    std::deque<std::string> operator()(std::string const &type_name) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_UTILITY_HH
