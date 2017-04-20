#ifndef PDDL_PARSER_ACTION_HH
#define PDDL_PARSER_ACTION_HH

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "condition.hh"
#include "effect.hh"
#include "typed_name.hh"

namespace pddl_parser {

class Action {
    std::string name;
    std::unordered_map<std::string, size_t> parameters_map;
    std::deque<TypedName> parameters;
    Condition condition;
    std::deque<Effect> effects;

public:
    Action() = default;
    Action(std::string &&name,
           std::deque<TypedName> &&parameters,
           Condition &&condition,
           std::deque<Effect> &&effects);

    std::string const & get_name() const { return name; }

    bool validate(
        std::unordered_map<std::string,TypedName> const &types,
        std::unordered_map<std::string,TypedName> const &constants) const;

    friend std::ostream& operator<<(std::ostream &stream, Action const &action);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_ACTION_HH
