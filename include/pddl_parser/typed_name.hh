#ifndef PDDL_PARSER_TYPED_NAME_H
#define PDDL_PARSER_TYPED_NAME_H

#include <cstddef>
#include <string>

#include "type.hh"

namespace pddl_parser {

class TypedName {
    std::string name;
    size_t type_index;

public:
    TypedName(std::string &&name, size_t type_index);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPED_NAME_H
