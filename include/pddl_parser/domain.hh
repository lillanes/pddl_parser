#ifndef PDDL_PARSER_DOMAIN_H
#define PDDL_PARSER_DOMAIN_H

#include <deque>
#include <iostream>
#include <unordered_map>
#include <string>

#include "action.hh"
#include "function.hh"
#include "predicate.hh"
#include "typed_name.hh"

namespace pddl_parser {

class Domain {
    std::string name;
    std::deque<std::string> requirements;
    std::unordered_map<std::string, TypedName> types;
    std::unordered_map<std::string, TypedName> constants;
    std::deque<Predicate> predicates;
    std::deque<Function> functions;
    std::deque<Action> actions;

public:
    Domain(std::string &&name,
           std::deque<std::string> &&requirements,
           std::unordered_map<std::string, TypedName> &&types,
           std::unordered_map<std::string, TypedName> &&constants,
           std::deque<Predicate> &&predicates,
           std::deque<Function> &&functions,
           std::deque<Action> &&actions);

    friend std::ostream& operator<<(std::ostream &stream, Domain const &domain);

};

} // namespace pddl_parser

#endif // PDDL_PARSER_DOMAIN_H
