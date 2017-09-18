#ifndef PDDL_PARSER_PREDICATE_HH
#define PDDL_PARSER_PREDICATE_HH

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

namespace pddl_parser {

struct TypedName;

struct Predicate {
    std::string name;
    std::deque<TypedName> variables;

    Predicate() = default;
    Predicate(std::string &&name, std::deque<TypedName> &&variables);

    bool validate(std::unordered_map<std::string,TypedName> const &types) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    Predicate const &predicate);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_PREDICATE_HH
