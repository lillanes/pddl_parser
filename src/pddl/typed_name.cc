#include <utility>

#include "typed_name.hh"

namespace pddl_parser {

TypedName::TypedName(std::string &&name, size_t type_index)
    : name(std::move(name)),
      type_index(type_index) {
}

} // namespace pddl_parser
