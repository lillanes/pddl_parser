#include <cstdlib>
#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <pddl_parser/action.hh>
#include <pddl_parser/condition.hh>
#include <pddl_parser/domain.hh>
#include <pddl_parser/effect.hh>
#include <pddl_parser/function.hh>
#include <pddl_parser/instance.hh>
#include <pddl_parser/numeric_expression.hh>
#include <pddl_parser/predicate.hh>
#include <pddl_parser/state.hh>
#include <pddl_parser/typed_name.hh>

using namespace pddl_parser;

int main(int, char **argv) {
    std::deque<std::string> requirements;
    std::deque<TypedName> types;
    std::deque<TypedName> constants;
    std::deque<Predicate> predicates;
    std::deque<Function> functions;
    std::deque<Action> actions;
    Condition condition;
    Effect effect;

    std::deque<PropositionalEffect> propositional_effects;
    std::deque<NumericEffect> numeric_effects;
    std::deque<Literal> propositional_conditions;
    std::deque<NumericComparison> numeric_conditions;
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

    condition = Condition(Literal("at", {"?t", "?from"}));

    propositional_effects.emplace_back(PropositionalEffect("at",
                                                           {"?t", "?from"},
                                                           false));
    propositional_effects.emplace_back(PropositionalEffect("at",
                                                           {"?t", "?to"},
                                                           true));

    effect = Effect(std::move(propositional_effects), {});

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?from", "location");
    variables.emplace_back("?to", "location");

    actions.emplace_back("move",
                         std::move(variables),
                         std::move(condition),
                         std::move(effect));

    propositional_conditions.emplace_back(Literal("at", {"?t", "?l"}));
    propositional_conditions.emplace_back(Literal("at", {"?b", "?l"}));
    lhs = NumericExpression(new AtomicExpression("weight", {"?t"}));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    lhs = NumericExpression(
        new BinaryExpression(BinaryOperator::PLUS,
                             std::move(lhs),
                             std::move(rhs)));
    rhs = NumericExpression(new AtomicExpression("max-weight", {"?t"}));
    numeric_conditions.emplace_back(NumericComparison(Comparator::LTE,
                                                      std::move(lhs),
                                                      std::move(rhs)));

    condition = Condition(std::move(propositional_conditions),
                          std::move(numeric_conditions));

    propositional_effects.emplace_back(PropositionalEffect("at",
                                                           {"?b", "?l"},
                                                           false));
    propositional_effects.emplace_back(PropositionalEffect("in",
                                                           {"?b", "?t"},
                                                           true));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    numeric_effects.emplace_back(NumericEffect(AssignmentOperator::INCREASE,
                                               "weight", {"?t"},
                                               std::move(rhs)));

    effect = Effect(std::move(propositional_effects),
                    std::move(numeric_effects));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?b", "box");
    variables.emplace_back("?l", "location");

    actions.emplace_back("load",
                         std::move(variables),
                         std::move(condition),
                         std::move(effect));

    propositional_conditions.emplace_back(Literal("at", {"?t", "?l"}));
    propositional_conditions.emplace_back(Literal("in", {"?b", "?t"}));

    condition = Condition(std::move(propositional_conditions), {});

    propositional_effects.emplace_back(PropositionalEffect("in",
                                                           {"?b", "?t"},
                                                           false));
    propositional_effects.emplace_back(PropositionalEffect("at",
                                                           {"?b", "?l"},
                                                           true));
    rhs = NumericExpression(new AtomicExpression("weight", {"?b"}));
    numeric_effects.emplace_back(NumericEffect(AssignmentOperator::DECREASE,
                                               "weight", {"?t"},
                                               std::move(rhs)));

    effect = Effect(std::move(propositional_effects),
                    std::move(numeric_effects));

    variables.emplace_back("?t", "truck");
    variables.emplace_back("?b", "box");
    variables.emplace_back("?l", "location");

    actions.emplace_back("unload",
                         std::move(variables),
                         std::move(condition),
                         std::move(effect));

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

    std::string output_str = output.str();
    std::string golden_str = golden.str();

    if (output_str == golden_str) {
        return EXIT_SUCCESS;
    }
    std::cout << "Read:" << std::endl;
    std::cout << output_str;
    std::cout << "Expected:" << std::endl;
    std::cout << golden_str;

    return EXIT_FAILURE;
}
