#include <fstream>

#include "driver.hh"

namespace pddl_parser {

Driver::Driver() :
    scanner(*this),
    parser(scanner, *this) {
}

int Driver::parse(std::string const &domain_fn,
                  std::deque<std::string> const &problem_fns) {
    std::ifstream domain(domain_fn);
    location.initialize(&domain_fn);
    scanner.switch_streams(&domain, nullptr);
    int error = parser.parse();
    if (error) {
        return error;
    }

    (void)problem_fns;
    for (auto &problem_fn : problem_fns) {
        std::ifstream problem(problem_fn);
        location.initialize(&problem_fn);
        scanner.switch_streams(&problem, nullptr);
        error = parser.parse();
    }
    return 0;
}

void Driver::incrementLocation(unsigned int loc) {
    location.step();
    location += loc;
}

void Driver::incrementLocationLine(unsigned int loc) {
    location.lines(loc);
}

void Driver::set_domain(Domain &&domain) {
    this->domain = std::move(domain);
}

} // namespace pddl_parser
