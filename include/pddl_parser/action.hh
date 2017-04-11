#ifndef PDDL_PARSER_ACTION_H
#define PDDL_PARSER_ACTION_H

#include <deque>
#include <iostream>
#include <string>
#include <memory>

#include "condition.hh"
#include "effect.hh"
#include "typed_name.hh"

namespace pddl_parser {

class Action {
    std::string name;
    std::deque<TypedName> parameters;
    std::unique_ptr<Condition> condition;
    std::deque<std::unique_ptr<Effect>> effects;

public:
    Action(std::string &&name,
           std::deque<TypedName> &&parameters,
           std::unique_ptr<Condition> &&condition,
           std::deque<std::unique_ptr<Effect>> &&effects);

    friend std::ostream& operator<<(std::ostream &stream, Action const &action);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_ACTION_H
