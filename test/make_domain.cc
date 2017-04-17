#include <cstdlib>
#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

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

int main(int, char **argv) {
    std::deque<std::string> requirements;
    std::deque<TypedName> types;
    std::deque<TypedName> constants;
    std::deque<Predicate> predicates;
    std::deque<Function> functions;
    std::deque<Action> actions;
    Condition condition;
    std::deque<Effect> effects;

    std::deque<Condition> conditions;
    std::deque<TypedName> variables;
    NumericExpression lhs;
    NumericExpression rhs;

    requirements.emplace_back(":typing");
    requirements.emplace_back(":fluents");

    types.emplace_back("locatable");
    types.emplace_back("location");
    types.emplace_back("truck", "locatable");
    types.emplace_back("box", "locatable");

    constants.emplace_back("depot", "location");

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

    condition = Condition(new Literal("at", {"?t", "?from"}));

    effects.emplace_back(Effect(new DeleteEffect("at", {"?t", "?from"})));
    effects.emplace_back(Effect(new AddEffect("at", {"?t", "?to"})));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?from", "location");
    variables.emplace_back("?to", "location");

    actions.emplace_back("move",
                         std::move(variables),
                         std::move(condition),
                         std::move(effects));

    conditions.emplace_back(Condition(new Literal("at", {"?t", "?l"})));
    conditions.emplace_back(Condition(new Literal("at", {"?b", "?l"})));
    lhs = NumericExpression(new AtomicExpression("weight", {"?t"}));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    lhs = NumericExpression(
        new BinaryExpression(BinaryOperator::PLUS,
                             std::move(lhs),
                             std::move(rhs)));
    rhs = NumericExpression(new AtomicExpression("max-weight", {"?t"}));
    conditions.emplace_back(Condition(new NumericComparison(Comparator::LTE,
                                                            std::move(lhs),
                                                            std::move(rhs))));

    condition = Condition(new Conjunction(std::move(conditions)));

    effects.emplace_back(Effect(new DeleteEffect("at", {"?b", "?l"})));
    effects.emplace_back(Effect(new AddEffect("in", {"?b", "?t"})));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    effects.emplace_back(Effect(new NumericEffect(AssignmentOperator::INCREASE,
                                                  "weight", {"?t"},
                                                  std::move(rhs))));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?b", "box");
    variables.emplace_back("?l", "location");

    actions.emplace_back("load",
                         std::move(variables),
                         std::move(condition),
                         std::move(effects));

    conditions.emplace_back(Condition(new Literal("at", {"?t", "?l"})));
    conditions.emplace_back(Condition(new Literal("in", {"?b", "?t"})));

    condition = Condition(new Conjunction(std::move(conditions)));

    effects.emplace_back(Effect(new DeleteEffect("in", {"?b", "?t"})));
    effects.emplace_back(Effect(new AddEffect("at", {"?b", "?l"})));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    effects.emplace_back(Effect(new NumericEffect(AssignmentOperator::DECREASE,
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


    // Golden file test:

    std::ostringstream output;
    output << domain;

    std::ifstream golden_file(argv[1]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    if (output.str() == golden.str()) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
