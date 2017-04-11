#ifndef PDDL_PARSER_NUMERIC_EXPRESSION_HH
#define PDDL_PARSER_NUMERIC_EXPRESSION_HH

#include <deque>
#include <string>
#include <memory>

namespace pddl_parser {

class NumericExpression {
};

class Number : public NumericExpression {
    double value;
public:
    Number(double value);
};

class AtomicExpression : public NumericExpression {
    std::string function_name;
    std::deque<std::string> parameters;

public:
    AtomicExpression(std::string &&function_name,
                     std::deque<std::string> &&parameters);
};

enum BinaryOperator {
    PLUS,
    MINUS,
    TIMES,
    DIV
};

class BinaryExpression : public NumericExpression {
    BinaryOperator binary_operator;
    std::unique_ptr<NumericExpression> lhs;
    std::unique_ptr<NumericExpression> rhs;

public:
    BinaryExpression(BinaryOperator binary_operator,
                     std::unique_ptr<NumericExpression> &&lhs,
                     std::unique_ptr<NumericExpression> &&rhs);
};

class InverseExpression : public NumericExpression {
    std::unique_ptr<NumericExpression> expression;

public:
    InverseExpression(std::unique_ptr<NumericExpression> &&expression);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_NUMERIC_EXPRESSION_HH
