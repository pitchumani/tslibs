cmake_minimum_required(VERSION 3.10)
project(tslibs_tests)

# Set output directory for test binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For unit tests, use the source directory as the include path
set(TSLIBS_UNIT_TESTS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(tsstack_test tsstack_test.cpp)
target_include_directories(tsstack_test PRIVATE ${TSLIBS_UNIT_TESTS_INCLUDE_DIR})

add_executable(tsqueue_test tsqueue_test.cpp)
target_include_directories(tsqueue_test PRIVATE ${TSLIBS_UNIT_TESTS_INCLUDE_DIR})

enable_testing()
add_test(NAME tsstack_test COMMAND tsstack_test)
add_test(NAME tsqueue_test COMMAND tsqueue_test)
