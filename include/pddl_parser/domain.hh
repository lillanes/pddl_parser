#ifndef PDDL_PARSER_DOMAIN_H
#define PDDL_PARSER_DOMAIN_H

#include <deque>
#include <string>

#include "action.hh"
#include "function.hh"
#include "predicate.hh"
#include "type.hh"
#include "typed_name.hh"

namespace pddl_parser {

class Domain {
    std::deque<std::string> requirements;
    std::deque<Type> types;
    std::deque<TypedName> constants;
    std::deque<Predicate> predicates;
    std::deque<Function> functions;
    std::deque<Action> actions;

};

} // namespace pddl_parser

#endif // PDDL_PARSER_DOMAIN_H
