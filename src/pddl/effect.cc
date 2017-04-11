#include <utility>

#include "effect.hh"

namespace pddl_parser {

AddEffect::AddEffect(std::string &&predicate_name,
                     std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

DeleteEffect::DeleteEffect(std::string &&predicate_name,
                           std::deque<std::string> &&parameters)
    : predicate_name(std::move(predicate_name)),
      parameters(std::move(parameters)) {
}

NumericEffect::NumericEffect(AssignmentOperator assigment_operator,
                             std::string &&function_name,
                             std::deque<std::string> &&parameters,
                             std::unique_ptr<NumericExpression> &&expression)
    : assignment_operator(assigment_operator),
      function_name(std::move(function_name)),
      parameters(std::move(parameters)),
      expression(std::move(expression)) {
}

} // namespace pddl_parser
