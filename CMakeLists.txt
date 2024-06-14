cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("parser-lab3-sample-programming-language" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME spl_peg_parser)
configure_file(config.hpp.in config.hpp)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME PEGParser
  VERSION 2.2.0
  GITHUB_REPOSITORY TheLartians/PEGParser
)

add_library(tree OBJECT tree.cpp)

add_library(spl_generator OBJECT spl_generator.cpp)
target_link_libraries(spl_generator
	tree
	PEGParser::PEGParser
)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_include_directories(${EXECUTABLE_NAME}
	PRIVATE
		${CMAKE_SOURCE_DIR}
		${CMAKE_BINARY_DIR}
)
target_link_libraries(${EXECUTABLE_NAME}
	tree
	spl_generator
)
