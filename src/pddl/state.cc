#include <pddl_parser/state.hh>

namespace pddl_parser {

GroundAtom::GroundAtom(std::string &&base_name,
                       std::deque<std::string> &&parameters)
    : base_name(std::move(base_name)),
      parameters(std::move(parameters)) {
}

std::string const & GroundAtom::get_base_name() const {
    return base_name;
}

std::deque<std::string> const & GroundAtom::get_parameters() const {
    return parameters;
}

std::ostream& operator<<(std::ostream &stream,
                         GroundAtom const &gp) {
    stream << "( " << gp.base_name << " ";
    for (auto const &p : gp.parameters) {
        stream << p << " ";
    }
    stream << ")";
    return stream;
}

GroundFunction::GroundFunction(
    std::string &&base_name,
    std::deque<std::string> &&parameters,
    double value)
    : GroundAtom(std::move(base_name), std::move(parameters)),
      value(value) {
}

double const & GroundFunction::get_value() const {
    return value;
}

std::ostream& operator<<(std::ostream &stream,
                         GroundFunction const &gf) {
    stream << "( = ( " << gf.base_name << " ";
    for (auto const &p : gf.parameters) {
        stream << p << " ";
    }
    stream << ") " << gf.value << " )";
    return stream;
}

State::State(std::deque<GroundAtom> &&propositional_state,
             std::deque<GroundFunction> &&numeric_state)
    : propositional_state(std::move(propositional_state)),
      numeric_state(std::move(numeric_state)) {
}

void State::add_predicate(std::string &&name,
                          std::deque<std::string> &&parameters) {
    propositional_state.emplace_back(std::move(name), std::move(parameters));
}

void State::add_function(std::string &&name,
                         std::deque<std::string> &&parameters,
                         double value) {
    numeric_state.emplace_back(std::move(name),
                               std::move(parameters),
                               value);
}

std::deque<GroundAtom> const & State::get_propositional_state() const {
    return propositional_state;
}

std::deque<GroundFunction> const & State::get_numeric_state() const {
    return numeric_state;
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
