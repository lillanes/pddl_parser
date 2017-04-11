#ifndef PDDL_PARSER_PREDICATE_H
#define PDDL_PARSER_PREDICATE_H

#include <deque>
#include <iostream>
#include <string>

#include "typed_name.hh"

namespace pddl_parser {

class Predicate {
    std::string name;
    std::deque<TypedName> variables;

public:
    Predicate(std::string &&name, std::deque<TypedName> &&variables);

    friend std::ostream& operator<<(std::ostream &stream,
                                    Predicate const &predicate);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_PREDICATE_H
