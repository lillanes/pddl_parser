#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "domain.hh"
#include "instance.hh"
#include "parse.hh"
#include "utility.hh"

using namespace pddl_parser;

int main(int, char **argv) {

    Domain domain = parse_domain(argv[1]);
    Instance instance = parse_instance(argv[2]);

    ObjectFetcher fetcher(domain, instance);

    TypedName const &t01 = fetcher("t01");
    TypedName const &depot = fetcher("depot");

    assert(t01.get_name() == "t01");
    assert(t01.get_type_name() == "truck");
    assert(depot.get_name() == "depot");
    assert(depot.get_type_name() == "location");

    return EXIT_SUCCESS;
}
