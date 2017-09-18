#ifndef PDDL_PARSER_CONDITION_HH
#define PDDL_PARSER_CONDITION_HH

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <pddl_parser/numeric_expression.hh>
#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct CanonicalCondition;

struct ConditionBase {
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const = 0;
    virtual CanonicalCondition canonicalize() const = 0;
    friend std::ostream& operator<<(std::ostream &stream,
                                    ConditionBase const &condition);

protected:
    friend class CopyableUniquePtr<ConditionBase>;
    virtual ConditionBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;

};

typedef CopyableUniquePtr<ConditionBase> Condition;

struct Conjunction : public ConditionBase {
    std::deque<Condition> conjuncts;

    Conjunction(std::deque<Condition> &&conjuncts);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;

private:
    ConditionBase * clone() const;
    void print(std::ostream &stream) const;
};

struct Literal : public ConditionBase {
    std::string predicate_name;
    std::deque<std::string> parameters;
    bool negated;

    Literal(std::string &&predicate_name,
            std::deque<std::string> &&parameters,
            bool negated=false);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;

private:
    ConditionBase * clone() const;
    void print(std::ostream &stream) const;
};

enum Comparator {
    LT,
    LTE,
    EQ,
    GTE,
    GT
};

struct NumericComparison : public ConditionBase {
    Comparator comparator;
    NumericExpression lhs;
    NumericExpression rhs;

    NumericComparison(Comparator comparator,
                      NumericExpression &&lhs,
                      NumericExpression &&rhs);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;
    CanonicalCondition canonicalize() const;

private:
    ConditionBase * clone() const;
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_HH
