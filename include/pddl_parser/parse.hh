#ifndef PDDL_PARSER_PARSER_HH
#define PDDL_PARSER_PARSER_HH

#include <deque>
#include <string>
#include <utility>

#include "domain.hh"
#include "instance.hh"

namespace pddl_parser {

std::pair<Domain,std::deque<Instance>> parse(
    char const *domain_fn, std::deque<char const *> instance_fns={});

std::pair<Domain,Instance> parse(char const *domain_fn,
                                 char const * instance_fn);

} // namespace pddl_parser

#endif // PDDL_PARSER_PARSER_HH
