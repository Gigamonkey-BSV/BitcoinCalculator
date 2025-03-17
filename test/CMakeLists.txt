cmake_minimum_required (VERSION 3.16)

# Back compatibility for VERSION range
if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy (VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

add_executable (unit_tests
  test_interpreter.cpp
)

target_link_libraries (unit_tests
  PRIVATE data gtest_main gmock)
gtest_discover_tests (unit_tests)
