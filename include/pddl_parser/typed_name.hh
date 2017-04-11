#ifndef PDDL_PARSER_TYPED_NAME_H
#define PDDL_PARSER_TYPED_NAME_H

#include <string>

#include "type.hh"

namespace pddl_parser {

class TypedName {
    std::string name;
    Type &type;

public:
    TypedName(std::string &&name, Type &type);

    void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPED_NAME_H
