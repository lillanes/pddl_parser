#include <cstdlib>
#include <fstream>
#include <sstream>

#include "domain.hh"
#include "parse.hh"

using namespace pddl_parser;

int main(int, char **argv) {

    auto parsed = parse(argv[1],
                        std::deque<char const *>(argv + 2, argv + 3));

    // Golden file test:

    std::ostringstream output;
    output << parsed.second.front();

    std::ifstream golden_file(argv[2]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    if (output.str() == golden.str()) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
