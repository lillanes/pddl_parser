#ifndef PDDL_PARSER_STATE_HH
#define PDDL_PARSER_STATE_HH

#include <deque>
#include <utility>
#include <string>

#include "condition.hh"

namespace pddl_parser {

class State {
    std::deque<Literal> propositional_state;
    std::deque<std::pair<std::string,double>> numeric_state;

public:
    State(std::deque<Literal> &&propositional_state,
          std::deque<std::pair<std::string,double>> numeric_state);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_STATE_HH
