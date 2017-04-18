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

class GroundPredicate {
    Predicate const &predicate;
    std::deque<std::reference_wrapper<TypedName const>> parameters;
public:
    GroundPredicate(Predicate const &predicate,
                    std::deque<std::reference_wrapper<TypedName const>> &&parameters);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundPredicate const &gp);
};

class GroundFunction {
    Function const &function;
    std::deque<std::reference_wrapper<TypedName const>> parameters;
    double value;
public:
    GroundFunction(Function const &function,
                   std::deque<std::reference_wrapper<TypedName const>> &&parameters,
                   double value);

    friend std::ostream& operator<<(std::ostream &stream,
                                    GroundFunction const &gf);
};

class State {
    std::deque<GroundPredicate> propositional_state;
    std::deque<GroundFunction> numeric_state;

public:
    State() = default;
    State(std::deque<GroundPredicate> &&propositional_state,
          std::deque<GroundFunction> &&numeric_state);

    void add_predicate(GroundPredicate &&gp);
    void add_function(GroundFunction &&gf);

    friend std::ostream& operator<<(std::ostream &stream, State const &state);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_STATE_HH
