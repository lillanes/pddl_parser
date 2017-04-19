#include <fstream>

#include "parser.bison.hh"

#include "parse.hh"
#include "scanner.hh"

namespace pddl_parser {

// std::pair<Domain,std::deque<Instance>> parse(
//     char const *domain_fn, std::deque<char const *> instance_fns) {
//     Scanner scanner;

//     // std::pair<Domain,std::deque<Instance>> output =
//     //     std::make_pair(Domain(), std::deque<Instance>());
//     Domain domain;
//     std::deque<Instance> instances;

//     scanner.initialize_location(domain_fn);
//     std::ifstream domain_stream(domain_fn);

//     Parser parser(scanner, domain, instances);

//     scanner.switch_streams(&domain_stream, nullptr);
//     int res = parser.parse();
//     if (res != 0) {
//         throw res;
//     }

//     for (char const *instance_fn : instance_fns) {
//         scanner.initialize_location(instance_fn);
//         std::ifstream instance_stream(instance_fn);
//         scanner.switch_streams(&instance_stream, nullptr);
//         res = parser.parse();
//         if (res != 0) {
//             throw res;
//         }
//     }

//     // return output;
// }

Domain parse_domain(char const *domain_fn) {
    Scanner scanner;

    scanner.initialize_location(domain_fn);
    std::ifstream domain_stream(domain_fn);

    Domain domain;
    Instance instance(domain);

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&domain_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    return domain;
}

Instance parse_instance(Domain &domain, char const *instance_fn) {
    Scanner scanner;

    scanner.initialize_location(instance_fn);
    std::ifstream instance_stream(instance_fn);

    Instance instance(domain);

    Parser parser(scanner, domain, instance);

    scanner.switch_streams(&instance_stream, nullptr);

    int res = parser.parse();
    if (res != 0) {
        throw res;
    }

    return instance;
}

} // namespace pddl_parser
