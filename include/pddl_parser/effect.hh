#ifndef PDDL_PARSER_EFFECT_H
#define PDDL_PARSER_EFFECT_H

#include <deque>
#include <string>
#include <memory>

#include "numeric_expression.hh"

namespace pddl_parser {

class Effect {
};

class AddEffect : Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);
};

class DeleteEffect : Effect {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    DeleteEffect(std::string &&predicate_name,
                 std::deque<std::string> &&parameters);
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
                  std::unique_ptr<NumericExpression> &&expression);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_H
