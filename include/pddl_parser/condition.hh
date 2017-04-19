#ifndef PDDL_PARSER_CONDITION_HH
#define PDDL_PARSER_CONDITION_HH

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
    void print(std::ostream &stream) const;

public:
    Conjunction(std::deque<Condition> &&conjuncts);
};

class Literal : public ConditionBase {
    std::string predicate_name;
    std::deque<std::string> parameters;
    bool negated;

    ConditionBase * clone() const;
    void print(std::ostream &stream) const;

public:
    Literal(std::string &&predicate_name,
            std::deque<std::string> &&parameters,
            bool negated=false);
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
    void print(std::ostream &stream) const;

public:
    NumericComparison(Comparator comparator,
                      NumericExpression &&lhs,
                      NumericExpression &&rhs);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_HH
