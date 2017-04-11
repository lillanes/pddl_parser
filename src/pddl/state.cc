#include <utility>

#include "state.hh"

namespace pddl_parser {

State::State(std::deque<Literal> &&propositional_state,
             std::deque<std::pair<std::string,double>> numeric_state)
    : propositional_state(std::move(propositional_state)),
      numeric_state(std::move(numeric_state)) {
}

} // namespace pddl_parser
