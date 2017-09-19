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

struct Literal {
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

    friend std::ostream& operator<<(std::ostream &stream,
                                    Literal const &literal);
};

enum Comparator {
    LT,
    LTE,
    EQ,
    GTE,
    GT
};

struct NumericComparison {
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

    friend std::ostream& operator<<(std::ostream &stream,
                                    NumericComparison const &comparison);
};

struct Condition {
    std::deque<Literal> propositional_conditions;
    std::deque<NumericComparison> numeric_conditions;

    Condition() = default;
    Condition(Literal &&literal);
    Condition(NumericComparison &&numeric_comparison);
    Condition(std::deque<Literal> &&propositional_conditions,
              std::deque<NumericComparison> &&numeric_conditions);

    void join_with(Condition &&other);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &parameters,
        std::string const &action_name) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    Condition const &condition);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CONDITION_HH
