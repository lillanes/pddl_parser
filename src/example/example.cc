#include <chrono>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "domain.hh"
#include "instance.hh"
#include "parse.hh"

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
            auto output = pddl_parser::parse(
                argv[1], std::deque<char const *>(argv + 2, argv + argc));
            timer.stop();
            std::cout << output.first;
            for (auto const &i : output.second) {
                std::cout << i;
            }
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
