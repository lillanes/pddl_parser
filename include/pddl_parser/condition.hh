#ifndef PDDL_PARSER_CONDITION_HH
#define PDDL_PARSER_CONDITION_HH

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "canonicalization.hh"
#include "numeric_expression.hh"
#include "typed_name.hh"

namespace pddl_parser {

class ConditionBase {
    friend class CopyableUniquePtr<ConditionBase>;
protected:
    virtual ConditionBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;
public:
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const = 0;
    virtual CanonicalCondition canonicalize() const = 0;
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

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;
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

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;
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

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;

    Comparator get_comparator() const;
    NumericExpression const & get_lhs() const;
    NumericExpression const & get_rhs() const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_HH
