#include <utility>

#include "type.hh"

namespace pddl_parser {

Type::Type(std::string &&name)
    : name(std::move(name)) {
}

DerivedType::DerivedType(std::string &&name, size_t parent_index)
    : Type(std::move(name)),
      parent_index(parent_index) {
}

DerivedType::DerivedType(std::string &&name)
    : Type(std::move(name)),
      parent_index(0) {
}

Either::Either(std::string &&name, std::deque<size_t> &&option_indices)
    : Type(std::move(name)),
      option_indices(std::move(option_indices)) {
}

Types::Types() {
    types.emplace_back(std::unique_ptr<Type>(new Type("object")));
}

}
