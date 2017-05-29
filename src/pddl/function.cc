#include <utility>

#include <pddl_parser/function.hh>

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

std::string const & Function::get_name() const {
    return name;
}

std::deque<TypedName> const & Function::get_variables() const {
    return variables;
}

std::ostream& operator<<(std::ostream &stream, Function const &function) {
    stream << "( " << function.name << " ";
    for (auto const &v : function.variables) {
        stream << v << " ";
    }
    stream << ")";
    return stream;
}

} // namespace pddl_parser
