file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_library(pddl STATIC ${sources})
