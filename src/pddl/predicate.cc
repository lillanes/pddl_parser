#include <utility>

#include "predicate.hh"

namespace pddl_parser {

Predicate::Predicate(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

std::ostream& operator<<(std::ostream &stream, Predicate const &predicate) {
    stream << "( " << predicate.name << " ";
    for (auto const &tn : predicate.variables) {
        stream << tn << " ";
    }
    stream << ")";

    return stream;
}

} // namespace pddl_parser
