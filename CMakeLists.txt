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
include_directories(include)
include_directories(src)

# Provide additional libraries' path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")

# Disable warnings from includes.
add_library(llvm INTERFACE)
target_sources(llvm INTERFACE)
target_include_directories(llvm PRIVATE include/ SYSTEM INTERFACE include/)

# Specify executable(s).
add_executable(${PROJECT_NAME} ${SOURCE_DIR})
