#include <utility>

#include "condition.hh"

namespace pddl_parser {

AtomicFormula::AtomicFormula(std::string &&predicate_name,
                             std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

Conjunction::Conjunction(std::deque<std::unique_ptr<Condition>> &&conjuncts)
    : conjuncts(std::move(conjuncts)) {
}

Literal::Literal(bool negated, AtomicFormula &&atom)
    : negated(negated),
      atom(std::move(atom)) {
}

NumericComparison::NumericComparison(Comparator comparator,
                                     NumericExpression &&lhs,
                                     NumericExpression &&rhs)
    : comparator(comparator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

} // namespace pddl_parser
