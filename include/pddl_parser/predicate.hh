#ifndef PDDL_PARSER_PREDICATE_HH
#define PDDL_PARSER_PREDICATE_HH

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

#include "typed_name.hh"

namespace pddl_parser {

class Predicate {
    std::string name;
    std::deque<TypedName> variables;

public:
    Predicate() = default;
    Predicate(std::string &&name, std::deque<TypedName> &&variables);

    std::string const & get_name() const;
    std::deque<TypedName> const & get_variables() const;

    bool validate(std::unordered_map<std::string,TypedName> const &types) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    Predicate const &predicate);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_PREDICATE_HH
