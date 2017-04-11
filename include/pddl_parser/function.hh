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
    Function(std::string &&name, std::deque<TypedName> &&variables);
};

class TypedFunction : Function {
    std::string type_name;

public:
    TypedFunction(std::string &&name,
                  std::deque<TypedName> &&variables,
                  std::string &&type_name);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_FUNCTION_H
