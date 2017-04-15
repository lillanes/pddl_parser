#ifndef DRIVER_HH
#define DRIVER_HH

#include <deque>
#include <string>

#include "parser.bison.hh"

#include "domain.hh"
#include "scanner.hh"

namespace pddl_parser {

class Driver
{
    friend class Scanner;
    friend class Parser;

    Scanner scanner;
    Parser parser;

    Domain domain;

    pddl_parser::location location;

    void set_domain(Domain &&domain);

    void incrementLocation(unsigned int loc);
    void incrementLocationLine(unsigned int loc);
public:
    Driver();

    int parse(std::string const &domain_fn,
              std::deque<std::string> const &problem_fns);

    Domain const & get_domain() const { return domain; }

};

} // PDDL

#endif // DRIVER_HH
