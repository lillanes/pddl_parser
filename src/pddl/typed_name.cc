#include <iostream>
#include <utility>

#include "typed_name.hh"

namespace pddl_parser {

TypedName::TypedName(std::string &&name, std::string &&type_name)
    : name(std::move(name)),
      type_name(std::move(type_name)) {
}

TypedName::TypedName(std::string &&name)
    : name(std::move(name)),
      type_name("object") {
}

std::ostream & operator<<(std::ostream &stream,
                          const pddl_parser::TypedName &tn) {
    stream << tn.name << " - " << tn.type_name;
    return stream;
}

} // namespace pddl_parser
