#ifndef PDDL_PARSER_ACTION_HH
#define PDDL_PARSER_ACTION_HH

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <pddl_parser/condition.hh>
#include <pddl_parser/effect.hh>
#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct Action {
    std::string name;
    std::unordered_map<std::string, size_t> parameters_map;
    std::deque<TypedName> parameters;
    Condition condition;
    Effect effect;

    Action() = default;
    Action(std::string &&name,
           std::deque<TypedName> &&parameters,
           Condition &&condition,
           Effect &&effect);

    bool validate(
        std::unordered_map<std::string,TypedName> const &types,
        std::unordered_map<std::string,TypedName> const &constants) const;

    friend std::ostream& operator<<(std::ostream &stream, Action const &action);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_ACTION_HH
