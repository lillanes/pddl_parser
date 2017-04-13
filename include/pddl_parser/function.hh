#ifndef PDDL_PARSER_FUNCTION_H
#define PDDL_PARSER_FUNCTION_H

#include <iostream>
#include <string>
#include <deque>

#include "typed_name.hh"

namespace pddl_parser {

class Function {
    std::string name;
    std::deque<TypedName> variables;

protected:
    virtual void print(std::ostream &stream) const;

public:
    Function(std::string &&name, std::deque<TypedName> &&variables);

    friend std::ostream& operator<<(std::ostream &stream,
                                    Function const &function);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_FUNCTION_H
