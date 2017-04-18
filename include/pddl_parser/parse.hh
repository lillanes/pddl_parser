#ifndef PDDL_PARSER_PARSER_HH
#define PDDL_PARSER_PARSER_HH

#include <deque>
#include <string>
#include <utility>

#include "domain.hh"
#include "instance.hh"

namespace pddl_parser {

// Domain parse_domain(std::string const &domain_fn);
// Instance parse_instance(Domain &domain, std::string const &domain_fn);

std::pair<Domain,std::deque<Instance>> parse(
    char const *domain_fn, std::deque<char const *> instance_fns={});

} // namespace pddl_parser

#endif // PDDL_PARSER_PARSER_HH
