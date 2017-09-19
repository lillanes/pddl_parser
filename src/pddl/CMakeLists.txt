set(sources
  "${CMAKE_CURRENT_SOURCE_DIR}/action.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/condition.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/domain.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/effect.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/function.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/numeric_expression.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/predicate.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/state.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/typed_name.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/utility.cc"
  )

add_library(pddl ${sources})

target_include_directories(pddl PUBLIC "${PROJECT_SOURCE_DIR}/include")

install(
  TARGETS pddl
  DESTINATION lib
  )
