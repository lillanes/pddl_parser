#ifndef PDDL_PARSER_TYPE_H
#define PDDL_PARSER_TYPE_H

#include <deque>
#include <memory>
#include <string>
#include <unordered_map>

namespace pddl_parser {

class Type {
protected:
    std::string name;

public:
    Type(std::string &&name);
    std::string &get_name() { return name; }
};

class DerivedType : Type {
    std::string parent_name;

public:
    DerivedType(std::string &&name, std::string &&parent_name);
    DerivedType(std::string &&name);
};

class Either : Type {
    std::deque<std::string> option_names;

public:
    Either(std::string &&name, std::deque<std::string> &&option_names);
};

class Types {
    std::unordered_map<std::string,std::unique_ptr<Type>> types;

public:
    Types();
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPE_H
