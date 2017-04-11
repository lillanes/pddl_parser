#include <utility>

#include "predicate.hh"

namespace pddl_parser {

Predicate::Predicate(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

} // namespace pddl_parser
