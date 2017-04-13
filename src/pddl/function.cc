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

} // namespace pddl_parser
