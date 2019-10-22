# General project settings.
cmake_minimum_required(VERSION 3.12.4)
project(ion_ir)

# Specify standard(s).
set(CMAKE_CXX_STANDARD 11)

# General project information.
set(PROJECT_URL "https://github.com/ionlang/ir-c")

# Setup source and build directories.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

option(USE_MD "Use MD instead of MTd" OFF)

if (USE_MD)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif(USE_MD)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# Setup versions.
set(CMAKE_CXX_STANDARD 17)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)")

# Configure and use LLVM. Also ensures LLVM 8.0.0 is installed.
find_package(LLVM 8.0 EXACT REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM source directories (for syntax support, etc.).
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

# Specify that this project is a library.
add_library(${PROJECT_NAME} ${SOURCES})

# Provide include directories to be used in the build command. Position in file matters.
#target_include_directories(${PROJECT_NAME} PRIVATE "src")
include_directories("src")

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries.
target_link_libraries(${PROJECT_NAME} ${llvm_libs})

# Setup unit testing using Google Test (GTest) if applicable. This binds the CMakeLists.txt on the test project.
option(PACKAGE_TESTS "Build tests" ON)

if (PACKAGE_TESTS)
    add_subdirectory(libs/googletest)
    add_subdirectory(test)
endif()
