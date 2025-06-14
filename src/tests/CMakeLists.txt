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

# Enable all compiler warnings, treat warnings as errors
add_compile_options(-Wall -Wextra -Werror)

enable_testing()
add_test(NAME tsstack_test COMMAND tsstack_test)
add_test(NAME tsqueue_test COMMAND tsqueue_test)

# Add custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tsstack_test tsqueue_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Run tests automatically after build
add_dependencies(run_tests tsstack_test tsqueue_test)
