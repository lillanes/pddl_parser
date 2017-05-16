#include <fstream>
#include <string>

#include "parser.bison.hh"

#include "parse.hh"
#include "scanner.hh"

namespace pddl_parser {

Domain parse_domain(char const *domain_fn) {
    Scanner scanner;

    scanner.initialize_location(domain_fn);
    std::ifstream domain_stream(domain_fn);

    if (!domain_stream.good()) {
        std::string error("error reading domain file (");
        error += domain_fn;
        error += ")";
        throw error;
    }

    Domain domain;
    Instance instance;

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&domain_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw std::string("failed to parse domain.");
    }

    return domain;
}

Instance parse_instance(char const *instance_fn) {
    Scanner scanner;

    scanner.initialize_location(instance_fn);
    std::ifstream instance_stream(instance_fn);

    if (!instance_stream.good()) {
        std::string error("error reading problem instance file (");
        error += instance_fn;
        error += ")";
        throw error;
    }


    Domain domain;
    Instance instance;

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&instance_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw std::string("failed to parse instance.");
    }

    return instance;
}

} // namespace pddl_parser
