#ifndef PDDL_PARSER_TYPE_H
#define PDDL_PARSER_TYPE_H

#include <deque>
#include <memory>
#include <string>

namespace pddl_parser {

class Type {
protected:
    std::string name;

public:
    static Type object;
    Type(std::string &&name);
    std::string &get_name() { return name; }

    void print(std::string &indent) const;
};

class DerivedType : Type {
    Type &parent;

public:
    DerivedType(std::string &&name, Type &parent);
    DerivedType(std::string &&name);

    void print(std::string &indent) const;
};

class Either : Type {
    std::deque<std::shared_ptr<Type>> options;

public:
    Either(std::string &&name, std::deque<std::shared_ptr<Type>> &&options);

    void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPE_H
