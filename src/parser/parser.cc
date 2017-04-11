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

    std::deque<Predicate> predicates;

    std::deque<Function> functions;

    std::deque<Action> actions;

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
