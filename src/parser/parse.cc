#include <fstream>

#include "parser.bison.hh"

#include "parse.hh"
#include "scanner.hh"

namespace pddl_parser {

std::pair<Domain,std::deque<Instance>> parse(
    char const *domain_fn, std::deque<char const *> instance_fns) {
    Scanner scanner;

    std::pair<Domain,std::deque<Instance>> output =
        std::make_pair(Domain(), std::deque<Instance>());

    scanner.initialize_location(domain_fn);
    std::ifstream domain_stream(domain_fn);

    Parser parser(scanner, output);

    scanner.switch_streams(&domain_stream, nullptr);
    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    for (char const *instance_fn : instance_fns) {
        scanner.initialize_location(instance_fn);
        std::ifstream instance_stream(instance_fn);
        scanner.switch_streams(&instance_stream, nullptr);
        res = parser.parse();
        if (res != 0) {
            throw res;
        }
    }

    return output;
}

std::pair<Domain,Instance> parse(char const *domain_fn,
                                 char const *instance_fn) {
    auto parsed = parse(domain_fn, std::deque<char const *>(1,instance_fn));

    return std::make_pair(parsed.first, parsed.second[0]);
}

} // namespace pddl_parser
