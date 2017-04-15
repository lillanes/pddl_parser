#ifndef PDDL_PARSER_EFFECT_H
#define PDDL_PARSER_EFFECT_H

#include <deque>
#include <iostream>
#include <string>
#include <memory>

#include "numeric_expression.hh"

namespace pddl_parser {

class EffectBase {
    friend class CopyableUniquePtr<EffectBase>;
protected:
    virtual EffectBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;
public:
    friend std::ostream& operator<<(std::ostream &stream, EffectBase const &effect);
};

typedef CopyableUniquePtr<EffectBase> Effect;

class AddEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    EffectBase * clone() const;

public:
    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);
    void print(std::ostream &stream) const;
};

class DeleteEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    EffectBase * clone() const;

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

class NumericEffect : public EffectBase {
    AssignmentOperator assignment_operator;
    std::string function_name;
    std::deque<std::string> parameters;
    NumericExpression expression;

    EffectBase * clone() const;

public:
    NumericEffect(AssignmentOperator assignment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  NumericExpression &&expression);
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_H
