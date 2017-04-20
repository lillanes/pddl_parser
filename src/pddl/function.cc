#include <utility>

#include "function.hh"

namespace pddl_parser {

Function::Function(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
}

bool Function::validate(
    std::unordered_map<std::string, TypedName> const &types) const {
    bool valid = true;
    for (TypedName const &variable : variables) {
        if (!variable.validate(types)) {
            std::cerr << "(in definition of function " << name << ")"
                      << std::endl;
            valid = false;
        }
    }
    return valid;
}

std::ostream& operator<<(std::ostream &stream, Function const &function) {
    function.print(stream);
    return stream;
}

void Function::print(std::ostream &stream) const {
    stream << "( " << name << " ";
    for (auto const &v : variables) {
        stream << v << " ";
    }
    stream << ")";
}

} // namespace pddl_parser
