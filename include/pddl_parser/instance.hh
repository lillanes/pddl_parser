#ifndef PDDL_PARSER_INSTANCE_HH
#define PDDL_PARSER_INSTANCE_HH

#include <deque>
#include <unordered_map>
#include <string>

#include "domain.hh"
#include "state.hh"

namespace pddl_parser {

class Instance {
    std::string name;
    Domain &domain;
    std::deque<std::string> requirements;
    std::unordered_map<std::string, TypedName> objects;
    State init;
    Condition goal;

public:
    Instance(std::string &&name,
             Domain &domain,
             std::deque<std::string> &&requirements,
             std::unordered_map<std::string, TypedName> &&objects,
             State &&init,
             Condition &&goal);
};

} // namespace pddl_parser

#endif // PDDL_PARSER_INSTANCE_HH
