cmake_minimum_required(VERSION 2.8)
project(pddl_parser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/include/pddl_parser)

add_subdirectory(src)

if (NOT PDDL_PARSER__DISABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
