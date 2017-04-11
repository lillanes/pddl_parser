#include <utility>

#include "action.hh"

namespace pddl_parser {

Action::Action(std::string &&name,
               std::deque<TypedName> &&parameters,
               std::unique_ptr<Condition> &&condition,
               std::deque<std::unique_ptr<Effect>> &&effects)
    : name(std::move(name)),
      parameters(std::move(parameters)),
      condition(std::move(condition)),
      effects(std::move(effects)) {
}

std::ostream& operator<<(std::ostream &stream, Action const &action) {
    stream << "( :action " << action.name << std::endl;
    stream << "   :parameters (" << std::endl;
    for (auto const &p : action.parameters) {
        stream << "    " << p << std::endl;
    }
    stream << "    )" << std::endl;
    stream << "   :precondition" << std::endl << *action.condition << std::endl;
    stream << "   :effect ( and" << std::endl;
    for (auto const &e : action.effects) {
        stream << "  " << *e << std::endl;
    }
    stream << "    ) )" << std::endl;
    return stream;
}

} // namespace pddl_parser
