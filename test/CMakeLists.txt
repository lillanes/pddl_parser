set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

add_executable(make_domain_test EXCLUDE_FROM_ALL make_domain.cc)
target_link_libraries(make_domain_test pddl)

include_directories(${CMAKE_BINARY_DIR}/src/parser)
include_directories(${CMAKE_SOURCE_DIR}/src/parser)

add_executable(read_domain_test EXCLUDE_FROM_ALL read_domain.cc)
target_link_libraries(read_domain_test parser)

add_custom_target(all_test_targets)
add_dependencies(all_test_targets make_domain_test read_domain_test)

add_test( # Not really a test, but it forces ctest to build the test targets.
  NAME build_tests
  COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target all_test_targets)
add_test(
  NAME make_domain_test
  COMMAND make_domain_test ${CMAKE_SOURCE_DIR}/test/golden/trucky.pddl)
add_test(
  NAME read_domain_test
  COMMAND read_domain_test ${CMAKE_SOURCE_DIR}/test/golden/trucky.pddl)
