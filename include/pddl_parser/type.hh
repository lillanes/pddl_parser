#ifndef PDDL_PARSER_TYPE_H
#define PDDL_PARSER_TYPE_H

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "typed_name.hh"

namespace pddl_parser {

class Type {
    friend class Types;
protected:
    std::string name;
    std::string parent_name;

public:
    Type(std::string &&name);
    Type(std::string &&name, std::string &&parent_name);
    friend std::ostream& operator<<(std::ostream& stream, const Type &type);
};

class Types {
    std::unordered_map<std::string,Type> types;

public:
    Types();

    void add_types(std::deque<TypedName> &&typed_names);
    Type& get_type(std::string &name);
    friend std::ostream& operator<<(std::ostream& stream, const Types &types);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPE_H
