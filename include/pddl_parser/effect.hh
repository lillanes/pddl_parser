#ifndef PDDL_PARSER_EFFECT_HH
#define PDDL_PARSER_EFFECT_HH

#include <deque>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include <pddl_parser/numeric_expression.hh>
#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct PropositionalEffect {
    std::string predicate_name;
    std::deque<std::string> parameters;
    bool is_add;

    PropositionalEffect(std::string &&predicate_name,
                        std::deque<std::string> &&parameters,
                        bool is_add);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    PropositionalEffect const &effect);
};

enum AssignmentOperator {
    ASSIGN,
    SCALE_UP,
    SCALE_DOWN,
    INCREASE,
    DECREASE
};

struct NumericEffect {
    AssignmentOperator assignment_operator;
    std::string function_name;
    std::deque<std::string> parameters;
    NumericExpression expression;

    NumericEffect(AssignmentOperator assignment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  NumericExpression &&expression);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    NumericEffect const &effect);
};

struct Effect {
    std::deque<PropositionalEffect> propositional_effects;
    std::deque<NumericEffect> numeric_effects;

    Effect() = default;
    Effect(PropositionalEffect &&propositional_effect);
    Effect(NumericEffect &&numeric_effect);
    Effect(std::deque<PropositionalEffect> &&propositional_effects,
           std::deque<NumericEffect> &&numeric_effects);

    void join_with(Effect &&other);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

    friend std::ostream& operator<<(std::ostream &stream, Effect const &effect);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_HH
