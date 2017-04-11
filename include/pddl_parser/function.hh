#ifndef PDDL_PARSER_FUNCTION_H
#define PDDL_PARSER_FUNCTION_H

#include <string>
#include <deque>

#include "typed_name.hh"

namespace pddl_parser {

class Function {
    std::string name;
    std::deque<TypedName> variables;

public:
    Function(std::string &&namge, std::deque<TypedName> &&variables);

    void print(std::string &indent) const;
};

class TypedFunction : Function {
    Type &type;

public:
    TypedFunction(std::string &&name,
                  std::deque<TypedName> &&variables,
                  Type &type);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_FUNCTION_H
