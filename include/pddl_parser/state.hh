#ifndef PDDL_PARSER_STATE_HH
#define PDDL_PARSER_STATE_HH

#include <deque>
#include <functional>
#include <iostream>
#include <string>

#include "function.hh"
#include "predicate.hh"
#include "typed_name.hh"

namespace pddl_parser {

class GroundAtom {
protected:
    std::string base_name;
    std::deque<std::string> parameters;
public:
    GroundAtom(std::string &&base_name, std::deque<std::string> &&parameters);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundAtom const &gp);
};

class GroundFunction : public GroundAtom {
    double value;
public:
    GroundFunction(std::string &&base_name,
                   std::deque<std::string> &&parameters,
                   double value);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundFunction const &gf);
};

class State {
    std::deque<GroundAtom> propositional_state;
    std::deque<GroundFunction> numeric_state;

public:
    State() = default;
    State(std::deque<GroundAtom> &&propositional_state,
          std::deque<GroundFunction> &&numeric_state);

    void add_predicate(std::string &&name, std::deque<std::string> &&parameters);
    void add_function(std::string &&name, std::deque<std::string> &&parameters,
                      double value);

    friend std::ostream& operator<<(std::ostream &stream, State const &state);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_STATE_HH
