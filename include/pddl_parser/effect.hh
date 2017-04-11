#ifndef PDDL_PARSER_EFFECT_H
#define PDDL_PARSER_EFFECT_H

#include <deque>
#include <iostream>
#include <string>
#include <memory>

#include "numeric_expression.hh"

namespace pddl_parser {

class Effect {
protected:
    virtual void print(std::ostream &stream) const = 0;
public:
    friend std::ostream& operator<<(std::ostream &stream, Effect const &effect);
};

class AddEffect : public Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);
    void print(std::ostream &stream) const;
};

class DeleteEffect : public Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    DeleteEffect(std::string &&predicate_name,
                 std::deque<std::string> &&parameters);
    void print(std::ostream &stream) const;
};

enum AssignmentOperator {
    ASSIGN,
    SCALE_UP,
    SCALE_DOWN,
    INCREASE,
    DECREASE
};

class NumericEffect : public Effect {
    AssignmentOperator assignment_operator;
    std::string function_name;
    std::deque<std::string> parameters;
    std::unique_ptr<NumericExpression> expression;

public:
    NumericEffect(AssignmentOperator assigment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  std::unique_ptr<NumericExpression> &&expression);
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_H
