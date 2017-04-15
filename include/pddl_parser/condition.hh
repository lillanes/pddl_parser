#ifndef PDDL_PARSER_CONDITION_H
#define PDDL_PARSER_CONDITION_H

#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "numeric_expression.hh"

namespace pddl_parser {

class ConditionBase {
    friend class CopyableUniquePtr<ConditionBase>;
protected:
    virtual ConditionBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;
public:
    friend std::ostream& operator<<(std::ostream &stream,
                                    ConditionBase const &condition);
};

typedef CopyableUniquePtr<ConditionBase> Condition;

class Conjunction : public ConditionBase {
    std::deque<Condition> conjuncts;

    ConditionBase * clone() const;

public:
    Conjunction(std::deque<Condition> &&conjuncts);
    void print(std::ostream &stream) const;
};

class Literal : public ConditionBase {
    std::string predicate_name;
    std::deque<std::string> parameters;
    bool negated;

    ConditionBase * clone() const;

public:
    Literal(std::string &&predicate_name, std::deque<std::string> &&parameters, bool negated=false);
    void print(std::ostream &stream) const;
};

enum Comparator {
    LT,
    LTE,
    EQ,
    GTE,
    GT
};

class NumericComparison : public ConditionBase {
    Comparator comparator;
    NumericExpression lhs;
    NumericExpression rhs;

    ConditionBase * clone() const;

public:
    NumericComparison(Comparator comparator,
                      NumericExpression &&lhs,
                      NumericExpression &&rhs);
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_H
