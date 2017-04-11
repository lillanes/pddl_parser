#ifndef PDDL_PARSER_CONDITION_H
#define PDDL_PARSER_CONDITION_H

#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "numeric_expression.hh"

namespace pddl_parser {

class Condition {
protected:
    virtual void print(std::ostream &stream) const = 0;
public:
    friend std::ostream& operator<<(std::ostream &stream,
                                    Condition const &condition);
};

class AtomicFormula : public Condition {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AtomicFormula(std::string &&predicate_name,
                  std::deque<std::string> &&parameters);
    void print(std::ostream &stream) const;
};

class Conjunction : public Condition {
    std::deque<std::unique_ptr<Condition>> conjuncts;

public:
    Conjunction(std::deque<std::unique_ptr<Condition>> &&conjuncts);
    void print(std::ostream &stream) const;
};

class Truth : public Conjunction {
public:
    Truth();
};

class Literal : public Condition {
    bool negated;
    AtomicFormula atom;

public:
    Literal(bool negated, AtomicFormula &&atom);
    void print(std::ostream &stream) const;
};

enum Comparator {
    LT,
    LTE,
    EQ,
    GTE,
    GT
};

class NumericComparison : public Condition {
    Comparator comparator;
    std::unique_ptr<NumericExpression> lhs;
    std::unique_ptr<NumericExpression> rhs;

public:
    NumericComparison(Comparator comparator,
                      std::unique_ptr<NumericExpression> &&lhs,
                      std::unique_ptr<NumericExpression> &&rhs);
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_H
