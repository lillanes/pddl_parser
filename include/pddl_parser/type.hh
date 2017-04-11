#ifndef PDDL_PARSER_TYPE_H
#define PDDL_PARSER_TYPE_H

#include <cstddef>
#include <deque>
#include <memory>
#include <string>

namespace pddl_parser {

class Type {
protected:
    std::string name;

public:
    Type(std::string &&name);
    std::string &get_name() { return name; }
};

class DerivedType : Type {
    size_t parent_index;

public:
    DerivedType(std::string &&name, size_t parent_index);
    DerivedType(std::string &&name);
};

class Either : Type {
    std::deque<size_t> option_indices;

public:
    Either(std::string &&name, std::deque<size_t> &&options);
};

class Types {
    std::deque<std::unique_ptr<Type>> types;

public:
    Types();
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPE_H
