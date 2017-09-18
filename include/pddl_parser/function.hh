#ifndef PDDL_PARSER_FUNCTION_HH
#define PDDL_PARSER_FUNCTION_HH

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct Function {
    std::string name;
    std::deque<TypedName> variables;

    Function() = default;
    Function(std::string &&name, std::deque<TypedName> &&variables);

    bool validate(std::unordered_map<std::string,TypedName> const &types) const;

    friend std::ostream& operator<<(std::ostream &stream,
                                    Function const &function);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_FUNCTION_HH
