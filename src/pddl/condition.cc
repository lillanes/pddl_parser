#include <utility>

#include "condition.hh"

namespace pddl_parser {

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

} // namespace pddl_parser
