cmake_minimum_required(VERSION 3.10)
project(tsstack_tests)

# Allow user to specify a custom install prefix, default to ../../install if not set
if(NOT DEFINED CUSTOM_INSTALL_PREFIX)
    set(CUSTOM_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../../install")
endif()

# Set output directory for test binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find the installed tsstack header (header-only, installed as 'tsstack' with no .h)
find_path(TSSTACK_INCLUDE_DIR NAMES tsstack PATHS ${CUSTOM_INSTALL_PREFIX}/include)

if(NOT TSSTACK_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find tsstack in ${CUSTOM_INSTALL_PREFIX}/include. Please install the header first.")
endif()

add_executable(tsstack_test tsstack_test.cpp)
target_include_directories(tsstack_test PRIVATE ${TSSTACK_INCLUDE_DIR})

enable_testing()
add_test(NAME tsstack_test COMMAND tsstack_test)
