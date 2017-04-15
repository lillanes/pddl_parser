#include <utility>

#include "numeric_expression.hh"

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream,
                         NumericExpressionBase const &numeric_expression) {
    numeric_expression.print(stream);
    return stream;
}

Number::Number(double value)
    : value(value) {
}

NumericExpressionBase * Number::clone() const {
    return new Number(value);
}

void Number::print(std::ostream &stream) const {
    stream << value;
}

AtomicExpression::AtomicExpression(std::string &&function_name,
                                   std::deque<std::string> &&parameters)
    : function_name(std::move(function_name)),
      parameters(std::move(parameters)) {
}

NumericExpressionBase * AtomicExpression::clone() const {
    return new AtomicExpression(std::string(function_name),
                                std::deque<std::string>(parameters));
}

void AtomicExpression::print(std::ostream &stream) const {
    stream << "( " << function_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
}

BinaryExpression::BinaryExpression(BinaryOperator binary_operator,
                                   NumericExpression &&lhs,
                                   NumericExpression &&rhs)
    : binary_operator(binary_operator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

NumericExpressionBase * BinaryExpression::clone() const {
    return new BinaryExpression(binary_operator,
                                NumericExpression(lhs),
                                NumericExpression(rhs));
}

void BinaryExpression::print(std::ostream &stream) const {
    stream << "( ";
    if (binary_operator == BinaryOperator::PLUS) {
        stream << "+";
    }
    else if (binary_operator == BinaryOperator::MINUS) {
        stream << "-";
    }
    else if (binary_operator == BinaryOperator::TIMES) {
        stream << "*";
    }
    else if (binary_operator == BinaryOperator::DIV) {
        stream << "/";
    }
    stream << " " << lhs;
    stream << " " << rhs;
    stream << " )";
}

InverseExpression::InverseExpression(NumericExpression &&expression)
    : expression(std::move(expression)) {
}

NumericExpressionBase * InverseExpression::clone() const {
    return new InverseExpression(NumericExpression(expression));
}

void InverseExpression::print(std::ostream &stream) const {
    stream << "( - " << expression << " )";
}

} // namespace pddl_parser
