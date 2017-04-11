#include <utility>

#include "type.hh"

namespace pddl_parser {

Type::Type(std::string &&name)
    : name(std::move(name)),
      parent_name("object") {
}

Type::Type(std::string &&name, std::string &&parent_name)
    : name(std::move(name)),
      parent_name(std::move(parent_name)) {
}

std::ostream& operator<<(std::ostream &stream, const Type &type) {
    stream << type.name << " - " << type.parent_name;
    return stream;
}

Types::Types() {
    types.emplace("object", Type("object", "NONE"));
}

void Types::add_types(std::deque<TypedName> &&typed_names) {
    for (TypedName &tn : typed_names) {
        std::string key(tn.get_name());
        if (key.compare("object") != 0) {
            types.emplace(key, Type(std::move(tn.get_name()),
                                    std::move(tn.get_type_name())));
        }
    }
}

Type& Types::get_type(std::string &name) {
    return types.at(name);
}

std::ostream& operator<<(std::ostream &stream, const Types &types) {
    for (auto const &type : types.types) {
        stream << type.second << std::endl;
    }
    return stream;
}

}
