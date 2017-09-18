#include <iterator>

#include <pddl_parser/canonicalization.hh>
#include <pddl_parser/condition.hh>
#include <pddl_parser/copyable_unique_ptr.hh>
#include <pddl_parser/effect.hh>

namespace pddl_parser {

CanonicalBase::CanonicalBase(std::string predicate_name,
                             std::deque<std::string> parameters,
                             bool negated)
    : predicate_names(1, predicate_name),
      parameters(1, parameters),
      negations(1, negated) {
}

void CanonicalBase::join_with(CanonicalBase &&other) {
    predicate_names.insert(
        predicate_names.end(),
        std::make_move_iterator(other.predicate_names.begin()),
        std::make_move_iterator(other.predicate_names.end()));
    parameters.insert(parameters.end(),
                      std::make_move_iterator(other.parameters.begin()),
                      std::make_move_iterator(other.parameters.end()));
    negations.insert(negations.end(),
                     std::make_move_iterator(other.negations.begin()),
                     std::make_move_iterator(other.negations.end()));
}

CanonicalCondition::CanonicalCondition(std::string predicate_name,
                                       std::deque<std::string> parameters,
                                       bool negated)
    : CanonicalBase(predicate_name, parameters, negated) {
}

CanonicalCondition::CanonicalCondition(
    NumericComparison const &numeric_comparison)
    : CanonicalBase(),
      numeric_comparisons(1, numeric_comparison) {
}

Condition CanonicalCondition::decanonicalize() {
    if (!numeric_comparisons.empty()) {
        std::cerr << "Conversion of canonical condition into PDDL condition is unimplemented!"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::deque<Condition> conjuncts;

    auto name = predicate_names.begin();
    auto params = parameters.begin();
    auto negated = negations.begin();

    while (name != predicate_names.end()) {
        conjuncts.emplace_back(new Literal(std::move(*name),
                                           std::move(*params),
                                           *negated));
        ++name;
        ++params;
        ++negated;
    }

    return Condition(new Conjunction(std::move(conjuncts)));
}

void CanonicalCondition::join_with(CanonicalCondition &&other) {
    CanonicalBase::join_with(static_cast<CanonicalBase&&>(other));
    numeric_comparisons.insert(
        numeric_comparisons.end(),
        std::make_move_iterator(other.numeric_comparisons.begin()),
        std::make_move_iterator(other.numeric_comparisons.end()));
}

CanonicalEffect::CanonicalEffect(std::string predicate_name,
                                 std::deque<std::string> parameters,
                                 bool negated)
    : CanonicalBase(predicate_name, parameters, negated) {}

CanonicalEffect::CanonicalEffect(NumericEffect const &numeric_effect)
    : CanonicalBase(),
      numeric_effects(1, numeric_effect) {
}

} // namespace pddl_parser
