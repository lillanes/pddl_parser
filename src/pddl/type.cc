#include <utility>

#include "type.hh"

namespace pddl_parser {

Type::Type(std::string &&name)
    : name(std::move(name)) {
}

DerivedType::DerivedType(std::string &&name, std::string &&parent_name)
    : Type(std::move(name)),
      parent_name(std::move(parent_name)) {
}

DerivedType::DerivedType(std::string &&name)
    : Type(std::move(name)),
      parent_name("object") {
}

Either::Either(std::string &&name, std::deque<std::string> &&option_names)
    : Type(std::move(name)),
      option_names(std::move(option_names)) {
}

Types::Types() {
    types.emplace("object", std::unique_ptr<Type>(new Type("object")));
}

}
