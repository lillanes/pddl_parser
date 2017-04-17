#ifndef PDDL_PARSER_ACTION_HH
#define PDDL_PARSER_ACTION_HH

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
    Condition condition;
    std::deque<Effect> effects;

public:
    Action() = default;
    Action(std::string &&name,
           std::deque<TypedName> &&parameters,
           Condition &&condition,
           std::deque<Effect> &&effects);

    friend std::ostream& operator<<(std::ostream &stream, Action const &action);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_ACTION_HH
