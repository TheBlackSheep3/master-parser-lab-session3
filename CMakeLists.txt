cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("parser-lab3-sample-programming-language" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME spl_parser)
configure_file(config.hpp.in config.hpp)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_include_directories(${EXECUTABLE_NAME}
	PRIVATE
		${CMAKE_SOURCE_DIR}
		${CMAKE_BINARY_DIR}
)
