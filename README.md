#### Getting started

Prepare the project, initialize and update required Git submodules:

```shell
$ git submodule update --init --recursive
```

Then, you'd want to invoke CMake to automatically build and compile the project:

```shell
$ cmake --build .
```

#### Usage

A general usage example is provided below.

```cpp
#include "ion_ir/generation/driver.hpp"
#include "ion_ir/syntax/lexer.hpp"
#include "ion_ir/syntax/stream.hpp"
#include "ion_ir/syntax/token.h"

int main() {
    // Create a lexer to tokenize input.
    Lexer lexer = new Lexer(...);

    // Tokenize the input.
    Stream<Token> stream = lexer.tokenize();

    // Create a driver to handle code generation.
    Driver driver = new Driver(stream);

    // Invoke the driver and capture its resulting LLVM IR code.
    std::string ir = driver.invoke();

    // Print out the resulting IR code.
    std::cout << ir;

    // Finish program.
    return 0;
}
```

#### Requirements

* CMake >=v3.13.X
* Python =v2.7
* Visual Studio 2019 with C++ tools (Windows)
* LLVM >=v9.0.0 (must build from source on Windows, see section below)


#### Installing LLVM (Linux)

Please refer to [this link](http://apt.llvm.org/) for instructions on installing LLVM on Linux systems. It is recommended to use the automatic installation script provided there.

#### Building LLVM

0. Ensure you have _all_ the requirements (excluding LLVM) installed, as the build process for LLVM will require Python, CMake and others.

1. Download and extract sources ([Visit LLVM's downloads page](http://releases.llvm.org/download.html)).

2. Build sources using a Windows command prompt with administrator privileges by issuing the following commands:

```
> cd <sources directory>
> cmake .
> cmake --build . --config Release --target INSTALL
```

3. LLVM sources, which are exclusively compatibly with CMake, shold now be available to be included in your `CMakeLists.txt` file. See example below:

```cmake
...
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Specify executable(s).
add_executable(${PROJECT_NAME} ${SOURCES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries.
target_link_libraries(${PROJECT_NAME} ${llvm_libs})
...
```

If you're running into trouble after building LLVM with Google Test (gtest) and getting the following error:

```
add_library cannot create target "gtest" because an imported target with
the same name already exists.
```

It's because both IonIR and LLVM incorporate Google Test, therefore building the Google Test project should be disabled when building LLVM from source:

```bash
$ cmake ... -DLLVM_INCLUDE_TESTS=OFF ...
```

#### Building project

* In Visual Studio Code, use `Clang X.0.0 for MSVC with Visual Studio Community 2019 (amd64)` as the build/compiler tool.
* When using CMake, first configure the project using `cmake --config Debug .` then build the executable using `cmake --build .`.
* Alternatively, configure the project using `cmake --config .` then build the executable with the default options using `cmake --build .`.

#### Running tests

Use the `ctest` command bundled with CMake to run tests.

Alternatively, build project & tests and run the tests executable generated.

#### Visual Studio Code notes

If intelli-sense is failing in Visual Studio Code, there may be a few reasons behind it:

* Try re-installing plugin.
* Compile project and its dependencies in your platform (ex. avoid using WSL on Windows).
* Ensure dependencies are properly installed and have correct versions.

#### Style Guide

This project adopts [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
