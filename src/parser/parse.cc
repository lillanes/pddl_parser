#include <fstream>

#include "parser.bison.hh"

#include "parse.hh"
#include "scanner.hh"

namespace pddl_parser {

Domain parse_domain(char const *domain_fn) {
    Scanner scanner;

    scanner.initialize_location(domain_fn);
    std::ifstream domain_stream(domain_fn);

    Domain domain;
    Instance instance;

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&domain_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    return domain;
}

Instance parse_instance(char const *instance_fn) {
    Scanner scanner;

    scanner.initialize_location(instance_fn);
    std::ifstream instance_stream(instance_fn);

    Domain domain;
    Instance instance;

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&instance_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    return instance;
}

} // namespace pddl_parser
