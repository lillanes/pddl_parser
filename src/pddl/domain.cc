#include <utility>

#include "domain.hh"

namespace pddl_parser {

Domain::Domain(std::string &&name,
               std::deque<std::string> &&requirements,
               Types &&types,
               std::deque<TypedName> &&constants,
               std::deque<Predicate> &&predicates,
               std::deque<Function> &&functions,
               std::deque<Action> &&actions)
    : name(std::move(name)),
      requirements(std::move(requirements)),
      types(std::move(types)),
      constants(std::move(constants)),
      predicates(std::move(predicates)),
      functions(std::move(functions)),
      actions(std::move(actions)) {
}

std::ostream& operator<<(std::ostream &stream, Domain const &domain) {
    stream << "( define ( domain " << domain.name << " )" << std::endl;

    stream << "  (:requirements ";
    for (auto const &r : domain.requirements) {
        stream << r << " ";
    }
    stream << ")" << std::endl;

    stream << "  " << domain.types << std::endl;

    stream << "  (:constants ";
    for (auto const &c : domain.constants) {
        stream << c << " ";
    }
    stream << ")" << std::endl;

    stream << "  (:predicates" << std::endl;
    for (auto const &p : domain.predicates) {
        stream << "  " << p;
    }
    stream << "  )" << std::endl;

    stream << "  (:functions" << std::endl;
    for (auto const &f : domain.functions) {
        stream << "  " << f << std::endl;
    }
    stream << "  )" << std::endl;

    for (auto const &a : domain.actions) {
        stream << a << std::endl;
    }

    stream << " )" << std::endl;
    return stream;
}

} // namespace pddl_parser
