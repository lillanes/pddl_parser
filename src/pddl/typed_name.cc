#include <iostream>
#include <utility>

#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

TypedName::TypedName(std::string &&name, std::string &&type_name)
    : name(std::move(name)),
      type_name(std::move(type_name)) {
}

TypedName::TypedName(std::string &&name)
    : name(std::move(name)),
      type_name("object") {
}

bool TypedName::validate(
    std::unordered_map<std::string,TypedName> const &types) const {
    if (!types.count(type_name)) {
        std::cerr << "ERROR: unknown type \"" << type_name << "\" ";
        return false;
    }
    return true;
}

std::ostream & operator<<(std::ostream &stream,
                          const pddl_parser::TypedName &tn) {
    stream << tn.name << " - " << tn.type_name;
    return stream;
}

} // namespace pddl_parser
