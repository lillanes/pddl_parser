file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_library(pddl STATIC ${sources})

target_include_directories(pddl
  PUBLIC "${PROJECT_SOURCE_DIR}/include/pddl_parser")
