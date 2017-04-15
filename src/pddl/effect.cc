#include <utility>

#include "effect.hh"

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream, EffectBase const &effect) {
    effect.print(stream);
    return stream;
}

AddEffect::AddEffect(std::string &&predicate_name,
                     std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

EffectBase * AddEffect::clone() const {
    return new AddEffect(std::string(predicate_name),
                         std::deque<std::string>(parameters));
}

void AddEffect::print(std::ostream &stream) const {
    stream << "( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
}

DeleteEffect::DeleteEffect(std::string &&predicate_name,
                           std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

EffectBase * DeleteEffect::clone() const {
    return new DeleteEffect(std::string(predicate_name),
                            std::deque<std::string>(parameters));
}

void DeleteEffect::print(std::ostream &stream) const {
    stream << "( not ( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ") )";
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

} // namespace pddl_parser
