set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

add_executable(make_domain_test EXCLUDE_FROM_ALL make_domain.cc)
target_link_libraries(make_domain_test pddl)

add_executable(read_domain_test EXCLUDE_FROM_ALL read_domain.cc)
target_link_libraries(read_domain_test pddl_parser)
add_executable(read_instance_test EXCLUDE_FROM_ALL read_instance.cc)
target_link_libraries(read_instance_test pddl_parser)
add_executable(object_fetcher_test EXCLUDE_FROM_ALL object_fetcher_test.cc)
target_link_libraries(object_fetcher_test pddl_parser)

add_custom_target(all_test_targets)
add_dependencies(all_test_targets
  make_domain_test
  read_domain_test
  read_instance_test
  pddl_parser_example,
  object_fetcher_test)

add_test( # Not really a test, but it forces ctest to build the test targets.
  NAME build_tests
  COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target all_test_targets)
add_test(
  NAME make_domain_test
  COMMAND make_domain_test ${PROJECT_SOURCE_DIR}/test/golden/trucky.pddl)
add_test(
  NAME read_domain_test
  COMMAND read_domain_test ${PROJECT_SOURCE_DIR}/test/golden/trucky.pddl)
add_test(
  NAME pddl_parser_example_test
  COMMAND pddl_parser_example ${PROJECT_SOURCE_DIR}/test/golden/trucky.pddl
                              ${PROJECT_SOURCE_DIR}/test/golden/trucky_p01.pddl
                              ${PROJECT_SOURCE_DIR}/test/golden/trucky_p01.pddl)
add_test(
  NAME object_fetcher_test
  COMMAND object_fetcher_test ${PROJECT_SOURCE_DIR}/test/golden/trucky.pddl
                              ${PROJECT_SOURCE_DIR}/test/golden/trucky_p01.pddl)
