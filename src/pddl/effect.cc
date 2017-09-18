#include <utility>

#include <pddl_parser/canonicalization.hh>
#include <pddl_parser/effect.hh>

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream, EffectBase const &effect) {
    effect.print(stream);
    return stream;
}

PropositionalEffect::PropositionalEffect(std::string &&predicate_name,
                                         std::deque<std::string> &&parameters,
                                         bool is_add)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)),
      is_add(is_add) {
}

EffectBase * PropositionalEffect::clone() const {
    return new PropositionalEffect(std::string(predicate_name),
                                   std::deque<std::string>(parameters),
                                   is_add);
}

void PropositionalEffect::print(std::ostream &stream) const {
    if (!is_add) {
        stream << "( not ";
    }
    stream << "( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
    if (!is_add) {
        stream << " )";
    }
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

CanonicalEffect PropositionalEffect::canonicalize() const {
    return CanonicalEffect(predicate_name, parameters, !is_add);
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

EffectBase * NumericEffect::clone() const {
    return new NumericEffect(assignment_operator,
                             std::string(function_name),
                             std::deque<std::string>(parameters),
                             NumericExpression(expression));
}

void NumericEffect::print(std::ostream &stream) const {
    stream << "( ";
    if (assignment_operator == AssignmentOperator::ASSIGN) {
        stream << "assign";
    }
    else if (assignment_operator == AssignmentOperator::INCREASE) {
        stream << "increase";
    }
    else if (assignment_operator == AssignmentOperator::DECREASE) {
        stream << "decrease";
    }
    else if (assignment_operator == AssignmentOperator::SCALE_UP) {
        stream << "scale-up";
    }
    else if (assignment_operator == AssignmentOperator::SCALE_DOWN) {
        stream << "scale-down";
    }
    stream << " ( " << function_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ") " << expression << " )";
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

CanonicalEffect NumericEffect::canonicalize() const {
    return CanonicalEffect(*this);
}

} // namespace pddl_parser
