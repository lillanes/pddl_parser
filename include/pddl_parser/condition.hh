#ifndef PDDL_PARSER_CONDITION_H
#define PDDL_PARSER_CONDITION_H

#include <deque>
#include <memory>
#include <string>

#include "numeric_expression.hh"

namespace pddl_parser {

class Condition {
};

class AtomicFormula : public Condition {
    std::string predicate_name;
    std::deque<std::string> parameters;

public:
    AtomicFormula(std::string &&predicate_name,
                  std::deque<std::string> &&parameters);
};

class Conjunction : public Condition {
    std::deque<std::unique_ptr<Condition>> conjuncts;

public:
    Conjunction(std::deque<std::unique_ptr<Condition>> &&conjuncts);
};

class Literal : public Condition {
    bool negated;
    AtomicFormula atom;

public:
    Literal(bool negated, AtomicFormula &&atom);
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
    NumericExpression lhs;
    NumericExpression rhs;

public:
    NumericComparison(Comparator comparator,
                      NumericExpression &&lhs,
                      NumericExpression &&rhs);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_H
