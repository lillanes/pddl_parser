#include <iterator>
#include <utility>

#include <pddl_parser/effect.hh>

namespace pddl_parser {

PropositionalEffect::PropositionalEffect(std::string &&predicate_name,
                                         std::deque<std::string> &&parameters,
                                         bool is_add)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)),
      is_add(is_add) {
}

bool PropositionalEffect::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    bool valid = true;
    for (std::string const &parameter : parameters) {
        if (!action_parameters.count(parameter)
            && !(constants.count(parameter))) {
            std::cerr << "ERROR: unknown parameter \"" << parameter << "\""
                      << " in effects of action \"" << action_name
                      << "\"" << std::endl;
            valid = false;
        }
    }
    return valid;
}

std::ostream& operator<<(std::ostream &stream,
                         PropositionalEffect const &effect) {
    if (!effect.is_add) {
        stream << "( not ";
    }
    stream << "( " << effect.predicate_name << " ";
    for (auto const &p : effect.parameters) {
        stream << p << " ";
    }
    stream << ")";
    if (!effect.is_add) {
        stream << " )";
    }
    return stream;
}

NumericEffect::NumericEffect(AssignmentOperator assignment_operator,
                             std::string &&function_name,
                             std::deque<std::string> &&parameters,
                             NumericExpression &&expression)
    : assignment_operator(assignment_operator),
      function_name(std::move(function_name)),
      parameters(std::move(parameters)),
      expression(std::move(expression)) {
}

bool NumericEffect::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    bool valid = true;
    for (std::string const &parameter : parameters) {
        if (!action_parameters.count(parameter)
            && !(constants.count(parameter))) {
            std::cerr << "ERROR: unknown parameter \"" << parameter << "\""
                      << " in effects of action \"" << action_name
                      << "\"" << std::endl;
            valid = false;
        }
    }
    if (!expression->validate(constants, action_parameters, action_name)) {
        valid = false;
    }
    return valid;
}

std::ostream& operator<<(std::ostream &stream, NumericEffect const &effect) {
    stream << "( ";
    if (effect.assignment_operator == AssignmentOperator::ASSIGN) {
        stream << "assign";
    }
    else if (effect.assignment_operator == AssignmentOperator::INCREASE) {
        stream << "increase";
    }
    else if (effect.assignment_operator == AssignmentOperator::DECREASE) {
        stream << "decrease";
    }
    else if (effect.assignment_operator == AssignmentOperator::SCALE_UP) {
        stream << "scale-up";
    }
    else if (effect.assignment_operator == AssignmentOperator::SCALE_DOWN) {
        stream << "scale-down";
    }
    stream << " ( " << effect.function_name << " ";
    for (auto const &p : effect.parameters) {
        stream << p << " ";
    }
    stream << ") " << effect.expression << " )";
    return stream;
}

Effect::Effect(PropositionalEffect &&propositional_effect)
    : propositional_effects(1, std::move(propositional_effect)) {
}

Effect::Effect(NumericEffect &&numeric_effect)
    : numeric_effects(1, std::move(numeric_effect)) {
}

Effect::Effect(std::deque<PropositionalEffect> &&propositional_effects,
               std::deque<NumericEffect> &&numeric_effects)
    : propositional_effects(std::move(propositional_effects)),
      numeric_effects(std::move(numeric_effects)) {
}

void Effect::join_with(Effect &&other) {
    propositional_effects.insert(
        propositional_effects.end(),
        std::make_move_iterator(other.propositional_effects.begin()),
        std::make_move_iterator(other.propositional_effects.end()));
    numeric_effects.insert(
        numeric_effects.end(),
        std::make_move_iterator(other.numeric_effects.begin()),
        std::make_move_iterator(other.numeric_effects.end()));
}

bool Effect::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    for (auto const &effect : propositional_effects) {
        if (!effect.validate(constants, action_parameters, action_name)) {
            return false;
        }
    }
    for (auto const &effect : numeric_effects) {
        if (!effect.validate(constants, action_parameters, action_name)) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &stream, Effect const &effect) {
    stream << "( and ";
    for (auto const &atom : effect.propositional_effects) {
        stream << atom << " ";
    }
    for (auto const &atom : effect.numeric_effects) {
        stream << atom << " ";
    }
    stream << ")";
    return stream;
}

} // namespace pddl_parser
