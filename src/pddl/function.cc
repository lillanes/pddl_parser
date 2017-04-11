#include <utility>

#include "function.hh"

namespace pddl_parser {

Function::Function(std::string &&name, std::deque<TypedName> &&variables)
    : name(std::move(name)),
      variables(std::move(variables)) {
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

TypedFunction::TypedFunction(std::string &&name,
                             std::deque<TypedName> &&variables,
                             std::string &&type_name)
    : Function(std::move(name), std::move(variables)),
      type_name(std::move(type_name)) {
}

void TypedFunction::print(std::ostream &stream) const {
    Function::print(stream);
    stream << " - " << type_name;
}

} // namespace pddl_parser
