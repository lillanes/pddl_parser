#include <cstdlib>
#include <deque>
#include <iostream>
#include <time.h>

#include "parser.bison.hh"

#include "driver.hh"
#include "scanner.hh"

struct Timer {
    struct timespec start_wall, finish_wall, start_cpu, finish_cpu;

    void start() {
        clock_gettime(CLOCK_MONOTONIC, &start_wall);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);
    }
    void finish() {
        clock_gettime(CLOCK_MONOTONIC, &finish_wall);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finish_cpu);
    }

    double get_wall() {
        double elapsed;
        elapsed = (finish_wall.tv_sec - start_wall.tv_sec);
        elapsed += (finish_wall.tv_nsec - start_wall.tv_nsec) / 1000000000.0;

        return elapsed;
    }
    double get_cpu() {
        double elapsed;
        elapsed = (finish_cpu.tv_sec - start_cpu.tv_sec);
        elapsed += (finish_cpu.tv_nsec - start_cpu.tv_nsec) / 1000000000.0;

        return elapsed;
    }
};

void print_usage(const char * name) {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << name
              << " domain.pddl [problem.pddl [problem2.pddl]...]" << std::endl;
}

int main(const int argc, const char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
    }
    else {
        Timer timer;

        timer.start();
        pddl_parser::Driver driver;
        std::deque<std::string> problem_fns(&argv[2], argv + argc);
        int res = driver.parse(argv[1], problem_fns);
        timer.finish();

        std::cout << driver.get_domain();


        std::cout << "Total time: " << timer.get_wall() << " seconds ("
                  << timer.get_cpu() << " CPU)." << std::endl;

        return res;
    }
    return EXIT_SUCCESS;
}
