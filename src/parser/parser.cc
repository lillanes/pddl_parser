#include <cstdlib>
#include <iostream>

#include "action.hh"
#include "condition.hh"
#include "domain.hh"
#include "effect.hh"
#include "function.hh"
#include "instance.hh"
#include "numeric_expression.hh"
#include "predicate.hh"
#include "state.hh"
#include "typed_name.hh"

using namespace pddl_parser;

int main(int, char **) {
    std::deque<std::string> requirements;
    std::unordered_map<std::string, TypedName> types;
    std::unordered_map<std::string, TypedName> constants;
    std::deque<Predicate> predicates;
    std::deque<Function> functions;
    std::deque<Action> actions;
    std::unique_ptr<Condition> condition;
    std::deque<std::unique_ptr<Effect>> effects;

    std::deque<std::unique_ptr<Condition>> conditions;
    std::deque<TypedName> variables;
    std::unique_ptr<NumericExpression> lhs;
    std::unique_ptr<NumericExpression> rhs;

    requirements.emplace_back(":typing");
    requirements.emplace_back(":fluents");

    types.emplace("locatable", TypedName("locatable"));
    types.emplace("location", TypedName("location"));
    types.emplace("truck", TypedName("truck", "locatable"));
    types.emplace("box", TypedName("box", "locatable"));

    constants.emplace("depot", TypedName("depot", "location"));

    variables.emplace_back("?x", "locatable");
    variables.emplace_back("?l", "location");
    predicates.emplace_back("at", std::move(variables));
    variables.emplace_back("?b", "box");
    variables.emplace_back("?t", "truck");
    predicates.emplace_back("in", std::move(variables));

    variables.emplace_back("?t", "truck");
    functions.emplace_back("max-weight", std::move(variables));
    variables.emplace_back("?x", "locatable");
    functions.emplace_back("weight", std::move(variables));

    condition = std::unique_ptr<Condition>(
        new AtomicFormula("at", {"?t", "?from"}));

    effects.emplace_back(std::unique_ptr<Effect>(
                             new DeleteEffect("at", {"?t", "?from"})));
    effects.emplace_back(std::unique_ptr<Effect>(
                             new AddEffect("at", {"?t", "?to"})));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?from", "location");
    variables.emplace_back("?to", "location");

    actions.emplace_back("move",
                         std::move(variables),
                         std::move(condition),
                         std::move(effects));

    conditions.emplace_back(std::unique_ptr<Condition>(
                                new AtomicFormula("at", {"?t", "?l"})));
    conditions.emplace_back(std::unique_ptr<Condition>(
                                new AtomicFormula("at", {"?b", "?l"})));
    lhs = std::unique_ptr<NumericExpression>(
        new AtomicExpression("weight", {"?t"}));
    rhs = std::unique_ptr<NumericExpression>(
        new AtomicExpression("weight", {"?b"}));
    lhs = std::unique_ptr<NumericExpression>(
        new BinaryExpression(BinaryOperator::PLUS,
                             std::move(lhs), std::move(rhs)));
    rhs = std::unique_ptr<NumericExpression>(
        new AtomicExpression("max-weight", {"?t"}));
    conditions.emplace_back(std::unique_ptr<Condition>(
                                new NumericComparison(Comparator::LTE,
                                                      std::move(lhs),
                                                      std::move(rhs))));

    condition = std::unique_ptr<Condition>(
        new Conjunction(std::move(conditions)));

    effects.emplace_back(std::unique_ptr<Effect>(
                             new DeleteEffect("at", {"?b", "?l"})));
    effects.emplace_back(std::unique_ptr<Effect>(
                             new AddEffect("in", {"?b", "?t"})));
    rhs = std::unique_ptr<NumericExpression>(
        new AtomicExpression("weight", {"?b"}));
    effects.emplace_back(std::unique_ptr<Effect>(
                             new NumericEffect(AssignmentOperator::INCREASE,
                                               "weight", {"?t"},
                                               std::move(rhs))));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?b", "box");
    variables.emplace_back("?l", "location");

    actions.emplace_back("load",
                         std::move(variables),
                         std::move(condition),
                         std::move(effects));

    conditions.emplace_back(std::unique_ptr<Condition>(
                                new AtomicFormula("at", {"?t", "?l"})));
    conditions.emplace_back(std::unique_ptr<Condition>(
                                new AtomicFormula("in", {"?b", "?t"})));

    condition = std::unique_ptr<Condition>(
        new Conjunction(std::move(conditions)));

    effects.emplace_back(std::unique_ptr<Effect>(
                             new DeleteEffect("in", {"?b", "?t"})));
    effects.emplace_back(std::unique_ptr<Effect>(
                             new AddEffect("at", {"?b", "?l"})));
    rhs = std::unique_ptr<NumericExpression>(
        new AtomicExpression("weight", {"?b"}));
    effects.emplace_back(std::unique_ptr<Effect>(
                             new NumericEffect(AssignmentOperator::DECREASE,
                                               "weight", {"?t"},
                                               std::move(rhs))));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?b", "box");
    variables.emplace_back("?l", "location");

    actions.emplace_back("unload",
                         std::move(variables),
                         std::move(condition),
                         std::move(effects));

    Domain domain("trucky",
                  std::move(requirements),
                  std::move(types),
                  std::move(constants),
                  std::move(predicates),
                  std::move(functions),
                  std::move(actions));

    std::cout << domain;

    return EXIT_SUCCESS;
}