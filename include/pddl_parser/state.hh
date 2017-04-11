#ifndef PDDL_PARSER_STATE_H
#define PDDL_PARSER_STATE_H

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

    void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_STATE_H
