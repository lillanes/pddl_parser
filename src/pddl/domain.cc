#include <utility>

#include "domain.hh"

namespace pddl_parser {

Domain::Domain(std::deque<std::string> &&requirements,
               Types &&types,
               std::deque<TypedName> &&constants,
               std::deque<Predicate> &&predicates,
               std::deque<Function> &&functions,
               std::deque<Action> &&actions)
    : requirements(std::move(requirements)),
      types(std::move(types)),
      constants(std::move(constants)),
      predicates(std::move(predicates)),
      functions(std::move(functions)),
      actions(std::move(actions)) {
}

} // namespace pddl_parser
