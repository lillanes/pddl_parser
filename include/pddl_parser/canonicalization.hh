#ifndef PDDL_PARSER_CANONICALIZATIONS_HH
#define PDDL_PARSER_CANONICALIZATIONS_HH

#include <cstddef>
#include <deque>
#include <string>

namespace pddl_parser {

class CanonicalBase {
protected:
    std::deque<std::string> predicate_names;
    std::deque<std::deque<std::string>> parameters;
    std::deque<bool> negations;

    CanonicalBase() = default;
    CanonicalBase(std::string predicate_name,
                  std::deque<std::string> parameters,
                  bool negated);
    void join_with(CanonicalBase &&other);
public:
    std::deque<std::string> const & get_predicate_names() const;
    std::deque<std::deque<std::string>> const & get_parameters() const;
    std::deque<bool> const & get_negations() const;
};

class NumericComparison;

class CanonicalCondition : public CanonicalBase {
    std::deque<NumericComparison> numeric_comparisons;

public:
    CanonicalCondition() = default;
    CanonicalCondition(std::string predicate_name,
                       std::deque<std::string> parameters,
                       bool negated);
    CanonicalCondition(NumericComparison const &numeric_comparison);
    void join_with(CanonicalCondition &&other);
};

class NumericEffect;

class CanonicalEffect : public CanonicalBase {
    std::deque<NumericEffect> numeric_effects;

public:
    CanonicalEffect() = default;
    CanonicalEffect(std::string predicate_name,
                    std::deque<std::string> parameters,
                    bool negated);
    CanonicalEffect(NumericEffect const &numeric_effect);
    void join_with(CanonicalEffect &&other);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CANONICALIZATIONS_HH
