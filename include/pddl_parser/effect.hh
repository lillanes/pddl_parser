#ifndef PDDL_PARSER_EFFECT_HH
#define PDDL_PARSER_EFFECT_HH

#include <deque>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "canonicalization.hh"
#include "condition.hh"
#include "numeric_expression.hh"
#include "typed_name.hh"

namespace pddl_parser {

class EffectBase {
    friend class CopyableUniquePtr<EffectBase>;
protected:
    virtual EffectBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;
public:
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const = 0;
    virtual CanonicalEffect canonicalize() const = 0;
    friend std::ostream& operator<<(std::ostream &stream,
                                    EffectBase const &effect);
};

typedef CopyableUniquePtr<EffectBase> Effect;

class AddEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    EffectBase * clone() const;
    void print(std::ostream &stream) const;

public:
    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
    CanonicalEffect canonicalize() const;
};

class DeleteEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    EffectBase * clone() const;
    void print(std::ostream &stream) const;

public:
    DeleteEffect(std::string &&predicate_name,
                 std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
    CanonicalEffect canonicalize() const;
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
    void print(std::ostream &stream) const;

public:
    NumericEffect(AssignmentOperator assignment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  NumericExpression &&expression);
    CanonicalEffect canonicalize() const;

    AssignmentOperator get_assignment_operator() const;
    std::string const & get_function_name() const;
    std::deque<std::string> const & get_parameters() const;
    NumericExpression const & get_expression() const;

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_HH
