#include <utility>

#include "function.hh"

namespace pddl_parser {

Function::Function(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

TypedFunction::TypedFunction(std::string &&name,
                             std::deque<TypedName> &&variables,
                             std::string &&type_name)
    : Function(std::move(name), std::move(variables)),
      type_name(std::move(type_name)) {
}

} // namespace pddl_parser
