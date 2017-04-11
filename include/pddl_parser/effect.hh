#ifndef PDDL_PARSER_EFFECT_H
#define PDDL_PARSER_EFFECT_H

#include <deque>
#include <string>
#include <memory>

#include "numeric_expression.hh"

namespace pddl_parser {

class Effect {
private:
    Effect() = delete;
public:
    virtual void print(std::string &indent) const = 0;
};

class AddEffect : Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);

    virtual void print(std::string &indent) const;
};

class DeleteEffect : Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    DeleteEffect(std::string &&predicate_name,
                 std::deque<std::string> &&parameters);

    virtual void print(std::string &indent) const;
};

enum AssignmentOperator {
    ASSIGN,
    SCALE_UP,
    SCALE_DOWN,
    INCREASE,
    DECREASE
};

class NumericEffect : Effect {
    AssignmentOperator assignment_operator;
    std::string function_name;
    std::deque<std::string> parameters;
    std::unique_ptr<NumericExpression> expression;

public:
    NumericEffect(AssignmentOperator assigment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  NumericExpression &&expression);

    virtual void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_H
