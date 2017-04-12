#include <utility>

#include "condition.hh"

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream, Condition const &condition) {
    condition.print(stream);
    return stream;
}

AtomicFormula::AtomicFormula(std::string &&predicate_name,
                             std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

void AtomicFormula::print(std::ostream &stream) const {
    stream << "( " << predicate_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
}

Conjunction::Conjunction(std::deque<std::unique_ptr<Condition>> &&conjuncts)
    : conjuncts(std::move(conjuncts)) {
}

void Conjunction::print(std::ostream &stream) const {
    stream << "( and ";
    for (auto const &conjunct : conjuncts) {
        stream << *conjunct << " ";
    }
    stream << ")";
}

Truth::Truth()
    : Conjunction(std::deque<std::unique_ptr<Condition>>()) {
}

Literal::Literal(bool negated, AtomicFormula &&atom)
    : negated(negated),
      atom(std::move(atom)) {
}

void Literal::print(std::ostream &stream) const {
    if (negated) {
        stream << "( not " << atom << " )";
    }
    else {
        stream << atom;
    }
}

NumericComparison::NumericComparison(Comparator comparator,
                                     std::unique_ptr<NumericExpression> &&lhs,
                                     std::unique_ptr<NumericExpression> &&rhs)
    : comparator(comparator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
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

    stream << " " << *lhs;
    stream << " " << *rhs;
    stream << " )";
}

} // namespace pddl_parser
