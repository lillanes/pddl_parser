#include "state.hh"

namespace pddl_parser {

GroundPredicate::GroundPredicate(
    Predicate const &predicate,
    std::deque<std::reference_wrapper<TypedName const>> &&parameters)
    : predicate(predicate),
      parameters(std::move(parameters)) {
}

std::ostream& operator<<(std::ostream &stream,
                         GroundPredicate const &gp) {
    stream << "( " << gp.predicate.get_name() << " ";
    for (auto const &p : gp.parameters) {
        stream << p.get().get_name() << " ";
    }
    stream << ")";
    return stream;
}

GroundFunction::GroundFunction(
    Function const &function,
    std::deque<std::reference_wrapper<TypedName const>> &&parameters,
    double value)
    : function(function),
      parameters(std::move(parameters)),
      value(value) {
}

std::ostream& operator<<(std::ostream &stream,
                         GroundFunction const &gf) {
    stream << "( = ( " << gf.function.get_name() << " ";
    for (auto const &p : gf.parameters) {
        stream << p.get().get_name() << " ";
    }
    stream << ") " << gf.value << " )";
    return stream;
}

State::State(std::deque<GroundPredicate> &&propositional_state,
             std::deque<GroundFunction> &&numeric_state)
    : propositional_state(std::move(propositional_state)),
      numeric_state(std::move(numeric_state)) {
}

void State::add_predicate(GroundPredicate &&gp) {
    propositional_state.emplace_back(std::move(gp));
}

void State::add_function(GroundFunction &&gf) {
    numeric_state.emplace_back(std::move(gf));
}

std::ostream& operator<<(std::ostream &stream, State const &state) {
    for (auto const &predicate : state.propositional_state) {
        stream << std::endl << "    " << predicate;
    }
    for (auto const &function : state.numeric_state) {
        stream << std::endl << "    " << function;
    }
    return stream;
}

} // namespace pddl_parser
