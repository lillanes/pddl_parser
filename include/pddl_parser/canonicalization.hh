#ifndef PDDL_PARSER_CANONICALIZATIONS_HH
#define PDDL_PARSER_CANONICALIZATIONS_HH

#include <cstddef>
#include <deque>
#include <string>

namespace pddl_parser {

struct CanonicalBase {
    std::deque<std::string> predicate_names;
    std::deque<std::deque<std::string>> parameters;
    std::deque<bool> negations;

    CanonicalBase() = default;
    CanonicalBase(std::string predicate_name,
                  std::deque<std::string> parameters,
                  bool negated);

protected:
    void join_with(CanonicalBase &&other);
};

struct ConditionBase;
template<class T> class CopyableUniquePtr;
typedef CopyableUniquePtr<ConditionBase> Condition;
struct NumericComparison;

struct CanonicalCondition : public CanonicalBase {
    std::deque<NumericComparison> numeric_comparisons;

    CanonicalCondition() = default;
    CanonicalCondition(std::string predicate_name,
                       std::deque<std::string> parameters,
                       bool negated);
    CanonicalCondition(NumericComparison const &numeric_comparison);
    void join_with(CanonicalCondition &&other);

    Condition decanonicalize();
};

struct NumericEffect;

struct CanonicalEffect : public CanonicalBase {
    std::deque<NumericEffect> numeric_effects;

    CanonicalEffect() = default;
    CanonicalEffect(std::string predicate_name,
                    std::deque<std::string> parameters,
                    bool negated);
    CanonicalEffect(NumericEffect const &numeric_effect);
    void join_with(CanonicalEffect &&other);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_CANONICALIZATIONS_HH
