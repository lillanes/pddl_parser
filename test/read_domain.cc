#include <cstdlib>
#include <fstream>
#include <sstream>

#include "driver.hh"
#include "domain.hh"

using namespace pddl_parser;

int main(int, char **argv) {

    Driver driver;

    driver.parse(argv[1], {});

    // Golden file test:

    std::ostringstream output;
    output << driver.get_domain();

    std::ifstream golden_file(argv[1]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    if (output.str() == golden.str()) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
