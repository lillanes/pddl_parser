#include <fstream>

#include "parser.bison.hh"

#include "parse.hh"
#include "scanner.hh"

namespace pddl_parser {

Domain parse(std::string const &domain_fn) {

    std::ifstream domain_stream(domain_fn);

    Scanner scanner;
    Domain domain;
    Parser parser(scanner, domain);

    scanner.switch_streams(&domain_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    return domain;
}

} // namespace pddl_parser
