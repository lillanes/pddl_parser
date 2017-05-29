#include <utility>

#include <pddl_parser/numeric_expression.hh>

namespace pddl_parser {

std::ostream& operator<<(std::ostream &stream,
                         NumericExpressionBase const &numeric_expression) {
    numeric_expression.print(stream);
    return stream;
}

Number::Number(double value)
    : value(value) {
}

NumericExpressionBase * Number::clone() const {
    return new Number(value);
}

void Number::print(std::ostream &stream) const {
    stream << value;
}

double Number::get_value() const {
    return value;
}

bool Number::validate(
    std::unordered_map<std::string,TypedName> const & /*constants*/,
    std::unordered_map<std::string,size_t> const & /*parameters*/,
    std::string const & /*action_name*/) const {
    return true;
}

AtomicExpression::AtomicExpression(std::string &&function_name,
                                   std::deque<std::string> &&parameters)
    : function_name(std::move(function_name)),
      parameters(std::move(parameters)) {
}

NumericExpressionBase * AtomicExpression::clone() const {
    return new AtomicExpression(std::string(function_name),
                                std::deque<std::string>(parameters));
}

void AtomicExpression::print(std::ostream &stream) const {
    stream << "( " << function_name << " ";
    for (auto const &p : parameters) {
        stream << p << " ";
    }
    stream << ")";
}

std::string const & AtomicExpression::get_function_name() const {
    return function_name;
}

std::deque<std::string> const & AtomicExpression::get_parameters() const {
    return parameters;
}

bool AtomicExpression::validate(
    std::unordered_map<std::string,TypedName> const & constants,
    std::unordered_map<std::string,size_t> const & action_parameters,
    std::string const &action_name) const {
    bool valid = true;
    for (std::string const &parameter : parameters) {
        if (!action_parameters.count(parameter)
            && !constants.count(parameter)) {
            std::cerr << "ERROR: unknown parameter \"" << parameter << "\""
                      << " in numeric expression in action \""
                      << action_name << "\"" << std::endl;
            valid = false;
        }
    }
    return valid;
}

BinaryExpression::BinaryExpression(BinaryOperator binary_operator,
                                   NumericExpression &&lhs,
                                   NumericExpression &&rhs)
    : binary_operator(binary_operator),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {
}

NumericExpressionBase * BinaryExpression::clone() const {
    return new BinaryExpression(binary_operator,
                                NumericExpression(lhs),
                                NumericExpression(rhs));
}

void BinaryExpression::print(std::ostream &stream) const {
    stream << "( ";
    if (binary_operator == BinaryOperator::PLUS) {
        stream << "+";
    }
    else if (binary_operator == BinaryOperator::MINUS) {
        stream << "-";
    }
    else if (binary_operator == BinaryOperator::TIMES) {
        stream << "*";
    }
    else if (binary_operator == BinaryOperator::DIV) {
        stream << "/";
    }
    stream << " " << lhs;
    stream << " " << rhs;
    stream << " )";
}

BinaryOperator BinaryExpression::get_binary_operator() const {
    return binary_operator;
}

NumericExpression const & BinaryExpression::get_lhs() const {
    return lhs;
}

NumericExpression const & BinaryExpression::get_rhs() const {
    return rhs;
}

bool BinaryExpression::validate(
    std::unordered_map<std::string,TypedName> const & constants,
    std::unordered_map<std::string,size_t> const & action_parameters,
    std::string const &action_name) const {
    return lhs->validate(constants, action_parameters, action_name)
        && rhs->validate(constants, action_parameters, action_name);
}

InverseExpression::InverseExpression(NumericExpression &&expression)
    : expression(std::move(expression)) {
}

NumericExpressionBase * InverseExpression::clone() const {
    return new InverseExpression(NumericExpression(expression));
}

void InverseExpression::print(std::ostream &stream) const {
    stream << "( - " << expression << " )";
}

NumericExpression const & InverseExpression::get_expression() const {
    return expression;
}

bool InverseExpression::validate(
    std::unordered_map<std::string,TypedName> const & constants,
    std::unordered_map<std::string,size_t> const & action_parameters,
    std::string const &action_name) const {
    return expression->validate(constants, action_parameters, action_name);
}

} // namespace pddl_parser
