file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_executable(parser ${sources})

target_link_libraries(parser pddl)
