#include <cstdlib>
#include <fstream>
#include <sstream>

#include "domain.hh"
#include "instance.hh"
#include "parse.hh"

using namespace pddl_parser;

int main(int, char **argv) {

    Domain domain = parse_domain(argv[1]);
    Instance instance = parse_instance(domain, argv[2]);

    // Golden file test:

    std::ostringstream output;
    output << instance;

    std::ifstream golden_file(argv[2]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    if (output.str() == golden.str()) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
