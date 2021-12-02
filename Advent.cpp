#include <argparse/argparse.hpp>
#include <stdexcept>

#include "Advent.hpp"

int
main(int argc, char** argv) {

    argparse::ArgumentParser program{"advent"};

    program.add_argument("--mode")
        .help("execute with mode (one of: run, time, benchmark)")
        .default_value(std::string{"run"})
        .required().nargs(1);
    
    program.add_argument("--day")
        .help("day to run (0 for all)")
        .scan<'d', int>().default_value(0)
        .required().nargs(1);

    program.add_argument("--part")
        .scan<'d', int>().default_value(3)
        .help("part to run (1, 2, or 3 [for all])")
        .required().nargs(1);
    
    program.add_argument("--ntimes")
        .scan<'d', int>().default_value(10)
        .help("number of times to run (for benchmarking)")
        .required().nargs(1);

    try {
        program.parse_args(argc, argv);
        types::options opts;

        if (auto const mode = program.get<std::string>("--mode"); mode.compare("run") == 0) {
            opts.modes = types::Run{};
        } else if (mode.compare("time") ==  0) {
            opts.modes = types::Time{};
        } else if (mode.compare("benchmark") == 0) {
            auto const ntimes = program.get<int>("--ntimes");
            opts.modes = types::Benchmark{ntimes};
        } else {
            throw std::runtime_error{"invalid option specified"};
        }

        if (auto const day = program.get<int>("--day"); day == 0) {
            opts.days = types::All{};
        } else {
            opts.days = types::Day{day};
        }

        if (auto const part = program.get<int>("--part"); part == 1 or part == 2) {
            opts.parts = types::Part{part};
        } else if (part == 3) {
            opts.parts = types::All{};
        }

        invoke(opts);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    
}
