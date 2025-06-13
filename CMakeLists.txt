cmake_minimum_required(VERSION 3.10)
project(tslibs)

# Set the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Install the header as 'tsstack' (no .h extension, like std headers)
install(FILES src/tsstack.h DESTINATION include RENAME tsstack)

# Build examples if the directory exists
if(EXISTS ${CMAKE_SOURCE_DIR}/examples)
    add_subdirectory(examples)
else()
    message(STATUS "No examples directory found, skipping example build.")
endif()
