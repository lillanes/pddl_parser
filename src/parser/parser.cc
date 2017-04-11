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

int main(int argc, char **argv) {
    (void)argc; (void)argv;

    std::deque<std::string> requirements;
    requirements.emplace_back(":typing");
    requirements.emplace_back(":fluents");

    std::unordered_map<std::string, TypedName> types;
    types.emplace("locatable", TypedName("locatable"));
    types.emplace("location", TypedName("location"));
    types.emplace("truck", TypedName("truck", "locatable"));
    types.emplace("box", TypedName("box", "locatable"));

    std::unordered_map<std::string, TypedName> constants;
    constants.emplace("depot", TypedName("depot", "location"));

    std::deque<TypedName> variables;

    std::deque<Predicate> predicates;
    variables.emplace_back("?x", "locatable");
    variables.emplace_back("?l", "location");
    predicates.emplace_back("at", std::move(variables));
    variables.emplace_back("?b", "box");
    variables.emplace_back("?t", "truck");
    predicates.emplace_back("in", std::move(variables));

    std::deque<Function> functions;
    variables.emplace_back("?t", "truck");
    functions.emplace_back("max-weight", std::move(variables));
    variables.emplace_back("?x", "locatable");
    functions.emplace_back("weight", std::move(variables));

    std::deque<Action> actions;

    std::unique_ptr<Condition> truth(new Truth());
    std::deque<std::unique_ptr<Effect>> effects;
    actions.emplace_back("noop",
                         std::move(variables),
                         std::move(truth),
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
