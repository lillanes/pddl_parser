#ifndef PDDL_PARSER_NUMERIC_EXPRESSION_HH
#define PDDL_PARSER_NUMERIC_EXPRESSION_HH

#include <deque>
#include <iostream>
#include <string>
#include <memory>

namespace pddl_parser {

class NumericExpression {
protected:
    virtual void print(std::ostream& stream) const = 0;
public:
    friend std::ostream& operator<<(std::ostream &stream,
                                    NumericExpression const &num_exp);
};

class Number : public NumericExpression {
    double value;
public:
    Number(double value);
    void print(std::ostream& stream) const;
};

class AtomicExpression : public NumericExpression {
    std::string function_name;
    std::deque<std::string> parameters;

public:
    AtomicExpression(std::string &&function_name,
                     std::deque<std::string> &&parameters);
    void print(std::ostream& stream) const;
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
    void print(std::ostream& stream) const;
};

class InverseExpression : public NumericExpression {
    std::unique_ptr<NumericExpression> expression;

public:
    InverseExpression(std::unique_ptr<NumericExpression> &&expression);
    void print(std::ostream& stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_NUMERIC_EXPRESSION_HH
