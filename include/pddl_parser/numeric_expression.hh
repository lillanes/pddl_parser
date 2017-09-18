#ifndef PDDL_PARSER_NUMERIC_EXPRESSION_HH
#define PDDL_PARSER_NUMERIC_EXPRESSION_HH

#include <deque>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include <pddl_parser/copyable_unique_ptr.hh>
#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct NumericExpressionBase {
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const = 0;
    friend std::ostream& operator<<(std::ostream &stream,
                                    NumericExpressionBase const &num_exp);

protected:
    friend class CopyableUniquePtr<NumericExpressionBase>;
    virtual NumericExpressionBase * clone() const = 0;
    virtual void print(std::ostream& stream) const = 0;
};

typedef CopyableUniquePtr<NumericExpressionBase> NumericExpression;

struct Number : public NumericExpressionBase {
    double value;

    Number(double value);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

private:
    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;
};

struct AtomicExpression : public NumericExpressionBase {
    std::string function_name;
    std::deque<std::string> parameters;

    AtomicExpression(std::string &&function_name,
                     std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

private:
    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;
};

enum BinaryOperator {
    PLUS,
    MINUS,
    TIMES,
    DIV
};

struct BinaryExpression : public NumericExpressionBase {
    BinaryOperator binary_operator;
    NumericExpression lhs;
    NumericExpression rhs;

    BinaryExpression(BinaryOperator binary_operator,
                     NumericExpression &&lhs,
                     NumericExpression &&rhs);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

private:
    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;
};

struct InverseExpression : public NumericExpressionBase {
    NumericExpression expression;
    CopyableUniquePtr<NumericExpressionBase> expression_;

    InverseExpression(NumericExpression &&expression);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

private:
    NumericExpressionBase * clone() const;
    void print(std::ostream& stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_NUMERIC_EXPRESSION_HH
