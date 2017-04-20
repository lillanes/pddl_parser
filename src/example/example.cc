#include <chrono>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "domain.hh"
#include "instance.hh"
#include "parse.hh"

using namespace pddl_parser;

struct Timer {
    struct timespec start_wall, finish_wall, start_cpu, finish_cpu;
    std::chrono::steady_clock::time_point start_time, end_time;

    void start() {
        start_time = std::chrono::steady_clock::now();
    }
    void stop() {
        end_time = std::chrono::steady_clock::now();
    }

    double get_elapsed() {
        std::chrono::duration<double> elapsed = end_time - start_time;

        return elapsed.count();
    }
};

void print_usage(char const * name) {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << name
              << " domain.pddl [problem.pddl [problem2.pddl]...]" << std::endl;
}

int main(int const argc, char const **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
    }
    else {
        Timer timer;

        try {
            timer.start();
            Domain domain = parse_domain(argv[1]);
            std::cout << domain;
            for (int i = 2; i < argc; ++i) {
                timer.start();
                Instance instance = parse_instance(argv[i]);
                std::cout << instance;
            }
            timer.stop();
            std::cout << "Parsing took "
                      << timer.get_elapsed() << " seconds." << std::endl;
        }
        catch (int error) {
            return error;
        }

        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
