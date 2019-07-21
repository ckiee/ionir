cmake_minimum_required(VERSION 3.13.1)
project(ion_ir_cpp)

set(CMAKE_CXX_STANDARD 17)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)")
include_directories(include)
include_directories(src)

add_executable(ion_ir "./src/Ion.IR.cpp")
