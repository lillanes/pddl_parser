#ifndef PDDL_PARSER_INSTANCE_H
#define PDDL_PARSER_INSTANCE_H

#include <deque>
#include <string>

#include "domain.hh"
#include "state.hh"

namespace pddl_parser {

class Instance {
    std::string name;
    Domain &domain;
    std::deque<std::string> requirements;
    std::deque<TypedName> objects;
    State init;
    std::unique_ptr<Condition> goal;

public:
    Instance(std::string &&name,
             Domain &domain,
             std::deque<std::string> &&requirements,
             std::deque<TypedName> &&objects,
             State &&init,
             std::unique_ptr<Condition> &&goal);

    void print(std::string &indent) const;
};

} // namespace pddl_parser

#endif // PDDL_PARSER_INSTANCE_H
