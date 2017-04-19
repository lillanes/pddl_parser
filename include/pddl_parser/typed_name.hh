#ifndef PDDL_PARSER_TYPED_NAME_HH
#define PDDL_PARSER_TYPED_NAME_HH

#include <string>

namespace pddl_parser {

class TypedName {
    std::string name;
    std::string type_name;

public:
    TypedName() = default;
    TypedName(std::string &&name);
    TypedName(std::string &&name, std::string &&type_name);

    std::string const &get_name() const { return name; }

    friend std::ostream & operator<<(std::ostream &stream,
                                     const TypedName &tn);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPED_NAME_HH
