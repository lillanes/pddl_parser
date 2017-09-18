#ifndef PDDL_PARSER_INSTANCE_HH
#define PDDL_PARSER_INSTANCE_HH

#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <pddl_parser/condition.hh>
#include <pddl_parser/state.hh>
#include <pddl_parser/typed_name.hh>

namespace pddl_parser {

struct Instance {
    std::string name;
    std::string domain_name;
    std::unordered_set<std::string> requirements;
    std::unordered_map<std::string, TypedName> objects;
    State init;
    Condition goal;

    void set_name(std::string &&name);
    void set_domain_name(std::string &&name);
    void set_requirements(std::deque<std::string> &&requirements);
    void set_objects(std::deque<TypedName> &&objects);
    void add_init_predicate(std::string &&name,
                            std::deque<std::string> &&parameters);
    void add_init_function(std::string &&name,
                           std::deque<std::string> &&parameters,
                           double value);
    void set_goal(Condition &&goal);

    Instance() = default;

    friend std::ostream& operator<<(std::ostream &stream,
                                    Instance const &instance);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_INSTANCE_HH
