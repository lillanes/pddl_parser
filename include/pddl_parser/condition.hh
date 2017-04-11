#ifndef PDDL_PARSER_CONDITION_H
#define PDDL_PARSER_CONDITION_H

#include <deque>
#include <memory>
#include <string>

#include "numeric_expression.hh"

namespace pddl_parser {

class Condition {
private:
    Condition() = delete;
public:
    virtual void print(std::string &indent) const = 0;
};

class AtomicFormula : Condition {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AtomicFormula(std::string &&name, std::deque<std::string> &&parameters);

    void print(std::string &indent) const;
};

class Conjunction : Condition {
    std::deque<std::unique_ptr<Condition>> conjuncts;

public:
    Conjunction(std::deque<std::unique_ptr<Condition>> &&conjuncts);

    void print(std::string &indent) const;
};

class Literal : Condition {
    bool negated;
    AtomicFormula atom;

public:
    Literal(bool negated, AtomicFormula &&atom);

    void print(std::string &indent) const;
};

enum Comparator {
    LT,
    LTE,
    EQ,
    GTE,
    GT
};

class NumericComparison : Condition {
    Comparator comparator;
    NumericExpression lhs;
    NumericExpression rhs;

public:
    NumericComparison(Comparator comparator,
                      NumericExpression &&lhs,
                      NumericExpression &rhs);

    void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_H
