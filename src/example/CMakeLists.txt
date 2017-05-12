set(sources
  "${CMAKE_CURRENT_SOURCE_DIR}/example.cc")

add_executable(
  pddl_parser_example
  EXCLUDE_FROM_ALL
  ${sources}
)

target_link_libraries(pddl_parser_example pddl_parser pddl)
