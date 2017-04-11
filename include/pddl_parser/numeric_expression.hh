#ifndef PDDL_PARSER_NUMERIC_EXPRESSION_HH
#define PDDL_PARSER_NUMERIC_EXPRESSION_HH

#include <deque>
#include <string>
#include <memory>

namespace pddl_parser {

class NumericExpression {
private:
    NumericExpression() = delete;
public:
    virtual void print(std::string &indent) const = 0;
};

class Number : NumericExpression {
    double value;
public:
    Number(double value);
};

class AtomicExpression {
    std::string function_name;
    std::deque<std::string> parameters;

public:
    AtomicExpression(std::string &&function_name,
                     std::deque<std::string> &&parameters);

    virtual void print(std::string &indent) const;
};

enum BinaryOperator {
    PLUS,
    MINUS,
    TIMES,
    DIV
};

class BinaryExpression {
    BinaryOperator binary_operator;
    std::unique_ptr<NumericExpression> lhs;
    std::unique_ptr<NumericExpression> rhs;

public:
    BinaryExpression(BinaryOperator binary_operator,
                     std::unique_ptr<NumericExpression> &&lhs,
                     std::unique_ptr<NumericExpression> &&rhs);

    virtual void print(std::string &indent) const;

};

class NegatedExpression {
    std::unique_ptr<NumericExpression> expression;

public:
    NegatedExpression(std::unique_ptr<NumericExpression> &&expression);

    virtual void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_NUMERIC_EXPRESSION_HH
