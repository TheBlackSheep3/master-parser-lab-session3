#include "spl_generator.hpp"
#include "tree.hpp"

namespace nd::spl::peg {
peg_parser::ParserGenerator<tree::INode> get_spl_parser_generator() {
  peg_parser::ParserGenerator<tree::INode> generator;
  return generator;
}
}  // namespace nd::spl::peg
