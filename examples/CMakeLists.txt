cmake_minimum_required(VERSION 3.10)
project(tslibs_examples)

# Allow user to specify a custom install prefix, default to ../install if not set
if(NOT DEFINED CUSTOM_INSTALL_PREFIX)
    set(CUSTOM_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../install")
endif()

# Set output directories to the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find the installed tsstack header (now header-only, installed as 'tsstack' with no .h)
find_path(TSSTACK_INCLUDE_DIR NAMES tsstack PATHS ${CUSTOM_INSTALL_PREFIX}/include)

if(NOT TSSTACK_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find tsstack in ${CUSTOM_INSTALL_PREFIX}/include. Please install the header first.")
endif()

add_executable(tsstack_example tsstack-example.cpp)
add_executable(stack_example stack-example.cpp)

target_include_directories(tsstack_example PRIVATE ${TSSTACK_INCLUDE_DIR})
target_include_directories(stack_example PRIVATE ${TSSTACK_INCLUDE_DIR})

add_custom_target(run_tsstack_example
    COMMENT "Run tsstack example"
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tsstack_example
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
add_custom_target(run_stack_example
    COMMENT "Run stack example"
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stack_example
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

add_custom_target(run_examples
    DEPENDS run_tsstack_example run_stack_example
    COMMENT "Running all examples..."
)
