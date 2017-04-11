#include <utility>

#include "action.hh"

namespace pddl_parser {

Action::Action(std::string &&name,
               std::deque<TypedName> &&parameters,
               std::unique_ptr<Condition> &&condition,
               std::deque<std::unique_ptr<Effect>> &&effects)
    : name(std::move(name)),
      parameters(std::move(parameters)),
      condition(std::move(condition)),
      effects(std::move(effects)) {
}

} // namespace pddl_parser
