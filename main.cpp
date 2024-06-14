#include <cstdlib>
#include <iostream>

#include "config.hpp"
#include "parameters.hpp"

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
    return EXIT_SUCCESS;
  }
}
