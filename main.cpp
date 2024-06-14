#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>

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
    auto genertor = nd::spl::peg::get_spl_parser_generator();
    try {
      std::cout << genertor.run("x:=1") << std::endl;
    } catch (std::exception& e) {
      std::cerr << "Parsing error:\n" << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
  }
}
