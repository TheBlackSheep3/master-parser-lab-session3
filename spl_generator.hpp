#pragma once

#include <peg_parser/generator.h>

#include "tree.hpp"

namespace nd::spl::peg {
peg_parser::ParserGenerator<tree::INode> get_spl_parser_generator();
}
