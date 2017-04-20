#ifndef PDDL_PARSER_NUMERIC_EXPRESSION_HH
#define PDDL_PARSER_NUMERIC_EXPRESSION_HH

#include <deque>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "copyable_unique_ptr.hh"
#include "typed_name.hh"

namespace pddl_parser {

class NumericExpressionBase {
    friend class CopyableUniquePtr<NumericExpressionBase>;
protected:
    virtual NumericExpressionBase * clone() const = 0;
    virtual void print(std::ostream& stream) const = 0;
public:
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const = 0;
    friend std::ostream& operator<<(std::ostream &stream,
                                    NumericExpressionBase const &num_exp);
};

typedef CopyableUniquePtr<NumericExpressionBase> NumericExpression;

class Number : public NumericExpressionBase {
    double value;

    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;

public:
    Number(double value);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
};

class AtomicExpression : public NumericExpressionBase {
    std::string function_name;
    std::deque<std::string> parameters;

    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;

public:
    AtomicExpression(std::string &&function_name,
                     std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
};

enum BinaryOperator {
    PLUS,
    MINUS,
    TIMES,
    DIV
};

class BinaryExpression : public NumericExpressionBase {
    BinaryOperator binary_operator;
    NumericExpression lhs;
    NumericExpression rhs;

    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;

public:
    BinaryExpression(BinaryOperator binary_operator,
                     NumericExpression &&lhs,
                     NumericExpression &&rhs);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
};

class InverseExpression : public NumericExpressionBase {
    NumericExpression expression;
    CopyableUniquePtr<NumericExpressionBase> expression_;

    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;

public:
    InverseExpression(NumericExpression &&expression);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_NUMERIC_EXPRESSION_HH
