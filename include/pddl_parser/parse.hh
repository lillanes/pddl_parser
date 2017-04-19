#ifndef PDDL_PARSER_PARSER_HH
#define PDDL_PARSER_PARSER_HH

#include <deque>
#include <string>
#include <utility>

#include "domain.hh"
#include "instance.hh"

namespace pddl_parser {

Domain parse_domain(char const *domain_fn);
Instance parse_instance(Domain &domain, char const *instance_fn);

} // namespace pddl_parser

#endif // PDDL_PARSER_PARSER_HH
