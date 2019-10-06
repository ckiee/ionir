# General project settings.
cmake_minimum_required(VERSION 3.13.1)
project(ion_ir)

# Setup source and build directories.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Setup versions.
set(CMAKE_CXX_STANDARD 17)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)")

# Provide include directories to be used in the build command.
#include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

# Configure and use LLVM.
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Disable warnings from includes.
#add_library(llvm INTERFACE)
#target_sources(llvm INTERFACE)
#target_include_directories(llvm PRIVATE include/ SYSTEM INTERFACE include/)

# Set source file(s).
set(SOURCES
    src/Ion.IR.cpp
)

# Specify executable(s).
add_executable(${PROJECT_NAME} ${SOURCES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries.
target_link_libraries(${PROJECT_NAME} ${llvm_libs})
