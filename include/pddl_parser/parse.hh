#ifndef PDDL_PARSER_PARSER_HH
#define PDDL_PARSER_PARSER_HH

#include <string>

#include "domain.hh"

namespace pddl_parser {

Domain parse(std::string const &domain_fn);

} // namespace pddl_parser

#endif // PDDL_PARSER_PARSER_HH
