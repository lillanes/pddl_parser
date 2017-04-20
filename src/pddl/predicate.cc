#include <utility>

#include "predicate.hh"

namespace pddl_parser {

Predicate::Predicate(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

bool Predicate::validate(
    std::unordered_map<std::string,TypedName> const &types) const {
    bool valid = true;
    for (TypedName const &variable : variables) {
        if (!variable.validate(types)) {
            std::cerr << "(in definition of predicate " << name << ")"
                      << std::endl;
            valid = false;
        }
    }
    return valid;
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
