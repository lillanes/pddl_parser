file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_executable(
  example
  EXCLUDE_FROM_ALL
  ${sources}
)

target_link_libraries(example parser pddl)
