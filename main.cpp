#include <exception>  // std::exception
#include <fstream>    // std::ifstream, std::ofstream
#include <iostream>   // std::cout, std::cerr, std::cin
#include <ostream>    // std::ostream
#include <string>     // std::string
#include <utility>    // std::move

#include <argparse/argparse.hpp>  // argparse::ArgumentParser

#include "config.hpp"
#include "parameters.hpp"
#include "spl_generator.hpp"

int main(int argc, char const* argv[]) {
  argparse::ArgumentParser program(PROJECT_EXECUTABLE, PROJECT_VERSION);
  program.add_argument("-o", "--output")
      .help("write output to OUTPUT_FILE")
      .metavar("OUTPUT_FILE");
  program.add_argument("-f", "--file")
      .help("read input from INPUT_FILE")
      .metavar("INPUT_FILE");
  program.add_description(
      "Parse code of the sample programming language, as described in "
      "semantics of programming languages, and put out a tree representing the "
      "program structure.");
  program.add_epilog("The code is parsed using a PEG parser.");

  try {
    program.parse_args(argc, argv);
  } catch (std::exception const& e) {
    std::cerr << e.what() << "\n\n" << HELP_HINT;
  }

  std::string parsable_string;
  Container<std::ostream> output_ptr;
  if (auto input_file = program.present("--file")) {
    std::ifstream file_stream{*input_file};
    file_stream >> parsable_string;
  } else {
    std::cin >> parsable_string;
  }
  if (auto output_file = program.present("--output")) {
    output_ptr = std::move(
        Container<std::ostream>{new std::ofstream(*output_file), true});
  } else {
    output_ptr = std::move(Container<std::ostream>{&std::cout, false});
  }

  auto generator = nd::spl::peg::get_spl_parser_generator();
  try {
    // *outstream_prt << generator.run(parsable_string) << std::endl;
  } catch (std::exception& e) {
    std::cerr << "Parsing error:\n" << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
