#include <cstdlib>
#include <fstream>
#include <sstream>

#include "domain.hh"
#include "parse.hh"

using namespace pddl_parser;

int main(int, char **argv) {

    Domain domain = parse(argv[1]);

    // Golden file test:

    std::ostringstream output;
    output << domain;

    std::ifstream golden_file(argv[1]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    if (output.str() == golden.str()) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}