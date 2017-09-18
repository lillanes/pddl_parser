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

struct CanonicalEffect;

struct EffectBase {
    virtual bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const = 0;
    virtual CanonicalEffect canonicalize() const = 0;
    friend std::ostream& operator<<(std::ostream &stream,
                                    EffectBase const &effect);

protected:
    friend class CopyableUniquePtr<EffectBase>;
    virtual EffectBase * clone() const = 0;
    virtual void print(std::ostream &stream) const = 0;

};

typedef CopyableUniquePtr<EffectBase> Effect;

struct AddEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    AddEffect(std::string &&predicate_name,
              std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
    CanonicalEffect canonicalize() const;

private:
    EffectBase * clone() const;
    void print(std::ostream &stream) const;
};

struct DeleteEffect : public EffectBase {
    std::string predicate_name;
    std::deque<std::string> parameters;

    DeleteEffect(std::string &&predicate_name,
                 std::deque<std::string> &&parameters);

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;
    CanonicalEffect canonicalize() const;

private:
    EffectBase * clone() const;
    void print(std::ostream &stream) const;
};

enum AssignmentOperator {
    ASSIGN,
    SCALE_UP,
    SCALE_DOWN,
    INCREASE,
    DECREASE
};

struct NumericEffect : public EffectBase {
    AssignmentOperator assignment_operator;
    std::string function_name;
    std::deque<std::string> parameters;
    NumericExpression expression;

    NumericEffect(AssignmentOperator assignment_operator,
                  std::string &&function_name,
                  std::deque<std::string> &&parameters,
                  NumericExpression &&expression);
    CanonicalEffect canonicalize() const;

    bool validate(
        std::unordered_map<std::string,TypedName> const &constants,
        std::unordered_map<std::string,size_t> const &action_parameters,
        std::string const &action_name) const;

private:
    EffectBase * clone() const;
    void print(std::ostream &stream) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_EFFECT_HH
