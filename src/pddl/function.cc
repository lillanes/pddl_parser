#include <utility>

#include "function.hh"

namespace pddl_parser {

Function::Function(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

TypedFunction::TypedFunction(std::string &&name,
              std::deque<TypedName> &&variables,
              size_t type_index)
    : Function(std::move(name), std::move(variables)),
      type_index(type_index) {
}

} // namespace pddl_parser
