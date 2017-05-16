#include <iterator>
#include <utility>

#include "condition.hh"

namespace pddl_parser {

CanonicalCondition::CanonicalCondition()
    : size(0),
      predicate_names(),
      parameters(),
      negations() {
}

CanonicalCondition::CanonicalCondition(
    size_t size,
    std::deque<std::string> predicate_names,
    std::deque<std::deque<std::string>> parameters,
    std::deque<bool> negations)
    : size(size),
      predicate_names(predicate_names),
      parameters(parameters),
      negations(negations) {
}

void CanonicalCondition::join_with(pddl_parser::CanonicalCondition &&other) {
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

std::ostream& operator<<(std::ostream &stream, ConditionBase const &condition) {
    condition.print(stream);
    return stream;
}

Literal::Literal(std::string &&predicate_name,
                 std::deque<std::string> &&parameters,
                 bool negated)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)),
      negated(negated) {
}

ConditionBase * Literal::clone() const {
    return new Literal(std::string(predicate_name),
                       std::deque<std::string>(parameters),
                       negated);
}

void Literal::print(std::ostream &stream) const {
    if (negated) {
        stream << "( not ( ";
    }
    stream << "( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
    if (negated) {
        stream << " )";
    }
}

bool Literal::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    bool valid = true;
    for (std::string const &parameter : parameters) {
        if (!action_parameters.count(parameter)
            && !constants.count(parameter)) {
            std::cerr << "ERROR: unknown parameter \"" << parameter << "\""
                      << " in conditions of action \"" << action_name << "\""
                      << std::endl;
            valid = false;
        }
    }
    return valid;
}

CanonicalCondition Literal::canonicalize() const {
    return CanonicalCondition(1, {predicate_name}, {parameters}, {negated});
}

Conjunction::Conjunction(std::deque<Condition> &&conjuncts)
    : conjuncts(std::move(conjuncts)) {
}

ConditionBase * Conjunction::clone() const {
    return new Conjunction(std::deque<Condition>(conjuncts));
}

void Conjunction::print(std::ostream &stream) const {
    stream << "( and ";
    for (auto const &conjunct : conjuncts) {
        stream << conjunct << " ";
    }
    stream << ")";
}

bool Conjunction::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    bool valid = true;
    for (Condition const &conjunct : conjuncts) {
        valid = conjunct->validate(constants, action_parameters, action_name)
            && valid;
    }
    return valid;
}

CanonicalCondition Conjunction::canonicalize() const {
    CanonicalCondition cc;
    for (auto const &conjunct : conjuncts) {
        cc.join_with(conjunct->canonicalize());
    }
    return cc;
}

NumericComparison::NumericComparison(Comparator comparator,
                                     NumericExpression &&lhs,
                                     NumericExpression &&rhs)
    : comparator(comparator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

ConditionBase * NumericComparison::clone() const {
    return new NumericComparison(comparator,
                                 NumericExpression(lhs),
                                 NumericExpression(rhs));
}

void NumericComparison::print(std::ostream &stream) const {
    stream << "( ";
    if (comparator == Comparator::LT) {
        stream << "< ";
    }
    else if (comparator == Comparator::LTE) {
        stream << "<=";
    }
    else if (comparator == Comparator::EQ) {
        stream << "=";
    }
    else if (comparator == Comparator::GTE) {
        stream << ">=";
    }
    else if (comparator == Comparator::GT) {
        stream << ">";
    }

    stream << " " << lhs;
    stream << " " << rhs;
    stream << " )";
}

bool NumericComparison::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    return lhs->validate(constants, action_parameters, action_name)
        && rhs->validate(constants, action_parameters, action_name);
}

CanonicalCondition NumericComparison::canonicalize() const {
    throw std::string(
        "Canonicalization of numeric comparisons is not supported.");
}


} // namespace pddl_parser
