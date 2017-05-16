#include <iterator>

#include "canonicalization.hh"
#include "condition.hh"
#include "effect.hh"

namespace pddl_parser {

CanonicalBase::CanonicalBase()
    : size(0) {
}

CanonicalBase::CanonicalBase(std::string predicate_name,
                             std::deque<std::string> parameters,
                             bool negated)
    : size(1),
      predicate_names(1, predicate_name),
      parameters(1, parameters),
      negations(1, negated) {
}

void CanonicalBase::join_with(CanonicalBase &&other) {
    size += other.size;
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

std::deque<std::string> const & CanonicalBase::get_predicate_names() const {
    return predicate_names;
}

std::deque<std::deque<std::string>> const & CanonicalBase::get_parameters() const {
    return parameters;
}

std::deque<bool> const & CanonicalBase::get_negations() const {
    return negations;
}

CanonicalCondition::CanonicalCondition(std::string predicate_name,
                                       std::deque<std::string> parameters,
                                       bool negated)
    : CanonicalBase(predicate_name, parameters, negated) {}

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

} // namespace pddl_parser
