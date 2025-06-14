cmake_minimum_required(VERSION 3.10)
project(tslibs_examples)

# Allow user to specify a custom install prefix, default to ../install if not set
if(NOT DEFINED CUSTOM_INSTALL_PREFIX)
    set(CUSTOM_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../install")
endif()

# Set output directories to the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find the installed tsstack header (now header-only, installed as 'tsstack' with no .h)
find_path(TSLIBS_INCLUDE_DIR NAMES tsstack tsqueue PATHS ${CUSTOM_INSTALL_PREFIX}/include)

if(NOT TSLIBS_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find tsstack in ${CUSTOM_INSTALL_PREFIX}/include. Please install the header first.")
endif()

# Enable all compiler warnings and treat them as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-private-field")

add_executable(tsstack_example tsstack-example.cpp)
add_executable(stack_example stack-example.cpp)
add_executable(tsqueue_example tsqueue-example.cpp)
add_executable(queue_example queue-example.cpp)

target_include_directories(tsstack_example PRIVATE ${TSLIBS_INCLUDE_DIR})
target_include_directories(stack_example PRIVATE ${TSLIBS_INCLUDE_DIR})
target_include_directories(tsqueue_example PRIVATE ${TSLIBS_INCLUDE_DIR})
target_include_directories(queue_example PRIVATE ${TSLIBS_INCLUDE_DIR})

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
add_custom_target(run_tsqueue_example
    COMMENT "Run tsqueue example"
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tsqueue_example
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
add_custom_target(run_queue_example
    COMMENT "Run queue example"
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/queue_example
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
add_custom_target(run_stdlib_examples
    DEPENDS run_stack_example run_queue_example
    COMMENT "Running all standard library examples..."
)
add_custom_target(run_tslib_examples
    DEPENDS run_tsstack_example run_tsqueue_example
    COMMENT "Running all tslibs examples..."
)
