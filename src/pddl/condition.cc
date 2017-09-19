#include <iterator>
#include <utility>

#include <pddl_parser/condition.hh>

namespace pddl_parser {

Literal::Literal(std::string &&predicate_name,
                 std::deque<std::string> &&parameters,
                 bool negated)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)),
      negated(negated) {
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

std::ostream& operator<<(std::ostream &stream, Literal const& literal) {
    if (literal.negated) {
        stream << "( not ( ";
    }
    stream << "( " << literal.predicate_name << " ";
    for (auto const &p : literal.parameters) {
        stream << p << " ";
    }
    stream << ")";
    if (literal.negated) {
        stream << " )";
    }
    return stream;
}

NumericComparison::NumericComparison(Comparator comparator,
                                     NumericExpression &&lhs,
                                     NumericExpression &&rhs)
    : comparator(comparator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

bool NumericComparison::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    return lhs->validate(constants, action_parameters, action_name)
        && rhs->validate(constants, action_parameters, action_name);
}

std::ostream& operator<<(std::ostream &stream,
                         NumericComparison const &comparison) {
    stream << "( ";
    if (comparison.comparator == Comparator::LT) {
        stream << "< ";
    }
    else if (comparison.comparator == Comparator::LTE) {
        stream << "<=";
    }
    else if (comparison.comparator == Comparator::EQ) {
        stream << "=";
    }
    else if (comparison.comparator == Comparator::GTE) {
        stream << ">=";
    }
    else if (comparison.comparator == Comparator::GT) {
        stream << ">";
    }

    stream << " " << comparison.lhs;
    stream << " " << comparison.rhs;
    stream << " )";

    return stream;
}

Condition::Condition(Literal &&literal)
    : propositional_conditions(1, std::move(literal)) {
}

Condition::Condition(NumericComparison &&numeric_comparison)
    : numeric_conditions(1, std::move(numeric_comparison)) {
}

Condition::Condition(std::deque<Literal> &&propositional_conditions,
                     std::deque<NumericComparison> &&numeric_conditions)
    : propositional_conditions(std::move(propositional_conditions)),
      numeric_conditions(std::move(numeric_conditions)) {
}

void Condition::join_with(Condition &&other) {
    propositional_conditions.insert(
        propositional_conditions.end(),
        std::make_move_iterator(other.propositional_conditions.begin()),
        std::make_move_iterator(other.propositional_conditions.end()));
    numeric_conditions.insert(
        numeric_conditions.end(),
        std::make_move_iterator(other.numeric_conditions.begin()),
        std::make_move_iterator(other.numeric_conditions.end()));
}

bool Condition::validate(
    std::unordered_map<std::string,TypedName> const &constants,
    std::unordered_map<std::string,size_t> const &action_parameters,
    std::string const &action_name) const {
    for (auto const &condition : propositional_conditions) {
        if (!condition.validate(constants, action_parameters, action_name)) {
            return false;
        }
    }
    for (auto const &condition : numeric_conditions) {
        if (!condition.validate(constants, action_parameters, action_name)) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &stream, Condition const &condition) {
    stream << "( and ";
    for (auto const &part : condition.propositional_conditions) {
        stream << part << " ";
    }
    for (auto const &part : condition.numeric_conditions) {
        stream << part << " ";
    }
    stream << ")";
    return stream;
}

} // namespace pddl_parser
