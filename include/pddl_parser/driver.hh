#ifndef DRIVER_HH
#define DRIVER_HH

#include <deque>
#include <string>

#include "parser.bison.hh"

#include "scanner.hh"

namespace pddl_parser {

class Driver
{
public:
    Driver();

    int parse(std::string const &domain_fn,
              std::deque<std::string> const &problem_fns);

    friend class Scanner;
    friend class Parser;

private:
    Scanner scanner;
    Parser parser;

    pddl_parser::location location;

    void incrementLocation(unsigned int loc);
    void incrementLocationLine(unsigned int loc);

};

} // PDDL

#endif // DRIVER_HH
