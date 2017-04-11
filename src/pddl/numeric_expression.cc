#include <utility>

#include "numeric_expression.hh"

namespace pddl_parser {

Number::Number(double value)
    : value(value) {
}

AtomicExpression::AtomicExpression(std::string &&function_name,
                                   std::deque<std::string> &&parameters)
    : function_name(std::move(function_name)),
      parameters(std::move(parameters)) {
}

BinaryExpression::BinaryExpression(BinaryOperator binary_operator,
                                   std::unique_ptr<NumericExpression> &&lhs,
                                   std::unique_ptr<NumericExpression> &&rhs)
    : binary_operator(binary_operator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

InverseExpression::InverseExpression(
    std::unique_ptr<NumericExpression> &&expression)
    : expression(std::move(expression)) {
}

} // namespace pddl_parser
