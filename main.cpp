#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>

#include "config.hpp"
#include "parameters.hpp"
#include "spl_generator.hpp"

void print_help() {
  std::cout << "Usage: " << PROJECT_EXECUTABLE << " [options] [INPUT_FILE]\n";
  std::cout << "  -o, --output OUTPUT_FILE   Write output to OUTPUT_FILE.\n";
  std::cout
      << "  -h, --help                 Print this help message and exit.\n";
  std::cout << "  -V, --version              Print the version of "
            << PROJECT_EXECUTABLE << " and exit.\n\n";
  std::cout << "If no INPUT_FILE is provided, input is read from stdin.\n";
}

void print_version() {
  std::cout << PROJECT_EXECUTABLE << " version " << PROJECT_VERSION
            << std::endl;
}

int main(int argc, char const* argv[]) {
  Parameters params{argv + 1, argv + argc};
  if (params.help_requested()) {
    print_help();
    return EXIT_SUCCESS;
  } else if (params.version_requested()) {
    print_version();
    return EXIT_SUCCESS;
  } else {
    std::string parsable_string{};
    Container<std::ostream> outstream_prt{};
    if (params.input_file().empty()) {
      parsable_string =
          std::string{std::istreambuf_iterator<char>(std::cin), {}};
    } else {
      std::ifstream file{params.input_file()};
      parsable_string = std::string{std::istreambuf_iterator<char>(file), {}};
    }
    if (!params.output_requested()) {
      outstream_prt = std::move(Container<std::ostream>{&std::cout, false});
    } else {
      if (!params.output_file().empty()) {
        outstream_prt = std::move(Container<std::ostream>{
            new std::ofstream{params.output_file()}, true});
      } else {
        std::cerr << "missing parameter OUTPUT_FILE\n\nRun '"
                  << PROJECT_EXECUTABLE << " " << HELP_LONG_FLAG
                  << "' for more informatin.\n";
        return EXIT_FAILURE;
      }
    }
    auto generator = nd::spl::peg::get_spl_parser_generator();
    try {
      *outstream_prt << generator.run(parsable_string) << std::endl;
    } catch (std::exception &e) {
      std::cerr << "Parsing error:\n" << e.what() << std::endl;
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}
