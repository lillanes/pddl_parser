#ifndef PDDL_PARSER_TYPED_NAME_HH
#define PDDL_PARSER_TYPED_NAME_HH

#include <string>
#include <unordered_map>

namespace pddl_parser {

struct TypedName {
    std::string name;
    std::string type_name;

    TypedName() = default;
    TypedName(std::string &&name);
    TypedName(std::string &&name, std::string &&type_name);

    bool validate(std::unordered_map<std::string,TypedName> const &types) const;

    friend std::ostream & operator<<(std::ostream &stream,
                                     const TypedName &tn);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_TYPED_NAME_HH
