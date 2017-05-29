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

    ObjectFetcher fetcher(domain, instance);

    TypedName const &t01 = fetcher("t01");
    TypedName const &depot = fetcher("depot");

    if(t01.get_name() != "t01") {
        return EXIT_FAILURE;
    }
    if(t01.get_type_name() != "truck") {
        return EXIT_FAILURE;
    }
    if(depot.get_name() != "depot") {
        return EXIT_FAILURE;
    }
    if(depot.get_type_name() != "location") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
