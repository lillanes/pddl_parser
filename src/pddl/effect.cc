#include <utility>

#include "effect.hh"

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream, Effect const &effect) {
    effect.print(stream);
    return stream;
}

AddEffect::AddEffect(std::string &&predicate_name,
                     std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
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

void DeleteEffect::print(std::ostream &stream) const {
    stream << "( not ( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ") )";
}

NumericEffect::NumericEffect(AssignmentOperator assigment_operator,
                             std::string &&function_name,
                             std::deque<std::string> &&parameters,
                             std::unique_ptr<NumericExpression> &&expression)
    : assignment_operator(assigment_operator),
      function_name(std::move(function_name)),
      parameters(std::move(parameters)),
      expression(std::move(expression)) {
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
    stream << std::endl << "  ( " << function_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")" << std::endl << "  " << *expression << "  )";
}

} // namespace pddl_parser
