#include <utility>

#include "numeric_expression.hh"

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream,
                         NumericExpression const &num_exp) {
    num_exp.print(stream);
    return stream;
}

Number::Number(double value)
    : value(value) {
}

void Number::print(std::ostream &stream) const {
    stream << value;
}

AtomicExpression::AtomicExpression(std::string &&function_name,
                                   std::deque<std::string> &&parameters)
    : function_name(std::move(function_name)),
      parameters(std::move(parameters)) {
}

void AtomicExpression::print(std::ostream &stream) const {
    stream << "( " << function_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
}

BinaryExpression::BinaryExpression(BinaryOperator binary_operator,
                                   std::unique_ptr<NumericExpression> &&lhs,
                                   std::unique_ptr<NumericExpression> &&rhs)
    : binary_operator(binary_operator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
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
    stream << " " << *lhs;
    stream << " " << *rhs;
    stream << " )";
}

InverseExpression::InverseExpression(
    std::unique_ptr<NumericExpression> &&expression)
    : expression(std::move(expression)) {
}

void InverseExpression::print(std::ostream &stream) const {
    stream << "( - " << *expression << " )";
}

} // namespace pddl_parser
