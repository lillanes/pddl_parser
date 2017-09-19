#include <utility>

#include <pddl_parser/action.hh>

namespace pddl_parser {

Action::Action(std::string &&name,
               std::deque<TypedName> &&parameters,
               Condition &&condition,
               Effect &&effect)
    : name(std::move(name)),
      parameters(std::move(parameters)),
      condition(std::move(condition)),
      effect(std::move(effect)) {
    size_t index = 0;
    for (auto const &pair : this->parameters) {
        parameters_map[pair.name] = index++;
    }
}

bool Action::validate(
    std::unordered_map<std::string, TypedName> const &types,
    std::unordered_map<std::string, TypedName> const &constants) const {
    bool valid = true;

    for (TypedName const &parameter : parameters) {
        if (!parameter.validate(types)) {
            std::cerr << "(in definition of action " << name << ")"
                      << std::endl;
            valid = false;
        }
    }

    valid = condition.validate(constants, parameters_map, name) && valid;
    valid = effect.validate(constants, parameters_map, name) && valid;

    return valid;
}

std::ostream& operator<<(std::ostream &stream, Action const &action) {
    stream << "  ( :action " << action.name << std::endl;
    stream << "    :parameters ( ";
    for (auto const &p : action.parameters) {
        stream << p << " ";
    }
    stream << ")" << std::endl;
    stream << "    :precondition " << action.condition << std::endl;
    stream << "    :effect " << action.effect << " )";
    return stream;
}

} // namespace pddl_parser
