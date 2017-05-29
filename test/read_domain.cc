#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include <pddl_parser/domain.hh>
#include <pddl_parser/parse.hh>

using namespace pddl_parser;

int main(int, char **argv) {

    auto parsed = parse_domain(argv[1]);

    // Golden file test:

    std::ostringstream output;
    output << parsed;

    std::ifstream golden_file(argv[1]);
    std::stringstream golden;
    golden << golden_file.rdbuf();

    std::string output_str = output.str();
    std::string golden_str = golden.str();

    if (output_str == golden_str) {
        return EXIT_SUCCESS;
    }
    std::cout << "Read:" << std::endl;
    std::cout << output_str;
    std::cout << "Expected:" << std::endl;
    std::cout << golden_str;

    return EXIT_FAILURE;
}
