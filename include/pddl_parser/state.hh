#ifndef PDDL_PARSER_STATE_HH
#define PDDL_PARSER_STATE_HH

#include <deque>
#include <functional>
#include <iostream>
#include <string>

namespace pddl_parser {

struct GroundAtom {
    std::string base_name;
    std::deque<std::string> parameters;

    GroundAtom(std::string &&base_name, std::deque<std::string> &&parameters);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundAtom const &gp);
};

struct GroundFunction : public GroundAtom {
    double value;

    GroundFunction(std::string &&base_name,
                   std::deque<std::string> &&parameters,
                   double value);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundFunction const &gf);
};

struct State {
    std::deque<GroundAtom> propositional_state;
    std::deque<GroundFunction> numeric_state;

    State() = default;
    State(std::deque<GroundAtom> &&propositional_state,
          std::deque<GroundFunction> &&numeric_state);

    void add_predicate(std::string &&name,
                       std::deque<std::string> &&parameters);
    void add_function(std::string &&name, std::deque<std::string> &&parameters,
                      double value);

    friend std::ostream& operator<<(std::ostream &stream, State const &state);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_STATE_HH
