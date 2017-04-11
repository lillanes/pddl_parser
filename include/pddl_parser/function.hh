#ifndef PDDL_PARSER_FUNCTION_H
#define PDDL_PARSER_FUNCTION_H

#include <cstddef>
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
    size_t type_index;

public:
    TypedFunction(std::string &&name,
                  std::deque<TypedName> &&variables,
                  size_t type_index);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_FUNCTION_H
