#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include <pddl_parser/domain.hh>
#include <pddl_parser/instance.hh>
#include <pddl_parser/parse.hh>
#include <pddl_parser/utility.hh>

using namespace pddl_parser;

int main(int, char **argv) {

    Domain domain = parse_domain(argv[1]);
    Instance instance = parse_instance(argv[2]);

    TypeChecker checker(domain);

    assert(checker("truck", "truck"));
    assert(checker("truck", "locatable"));
    assert(checker("truck", "object"));

    return EXIT_SUCCESS;
}
