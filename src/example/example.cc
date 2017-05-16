#include <chrono>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "domain.hh"
#include "instance.hh"
#include "parse.hh"

using namespace pddl_parser;

struct Timer {
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
        return EXIT_SUCCESS;
    }
    else {
        Timer timer;
        bool valid = true;

        try {
            timer.start();
            Domain domain = parse_domain(argv[1]);
            std::cout << domain;
            if (!domain.validate()) {
                valid = false;
            }
            for (int i = 2; i < argc; ++i) {
                timer.start();
                Instance instance = parse_instance(argv[i]);
                std::cout << instance;
            }
            timer.stop();
            std::cout << "Parsing took "
                      << timer.get_elapsed() << " seconds." << std::endl;
        }
        catch (std::string error) {
            std::cerr << "ERROR: " << error << std::endl;
            return EXIT_FAILURE;
        }

        if (valid) {
            return EXIT_SUCCESS;
        }
        else {
            return EXIT_FAILURE;
        }
    }
}
