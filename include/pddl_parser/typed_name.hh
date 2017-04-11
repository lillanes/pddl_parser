#ifndef PDDL_PARSER_TYPED_NAME_H
#define PDDL_PARSER_TYPED_NAME_H

#include <string>

namespace pddl_parser {

class TypedName {
    std::string name;
    std::string type_name;

public:
    TypedName(std::string &&name, std::string &&type_name);
    friend std::ostream & operator<<(std::ostream &stream,
                                     const TypedName &tn);

    std::string &get_name() { return name; }
    std::string &get_type_name() { return type_name; }
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPED_NAME_H
