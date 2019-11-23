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
#include <iostream>
#include <string>
#include "ionir/generation/driver.h"
#include "ionir/syntax/lexer.h"
#include "ionir/syntax/token.h"
#include "ionir/misc/iterator.h"

int main() {
    // Create a lexer to tokenize input.
    Lexer lexer = new Lexer("hello world");

    // Tokenize the input.
    TokenStream stream = lexer.scan();

    // Create a driver to handle code generation.
    Driver driver = new Driver(stream);

    // Invoke the driver and capture its resulting LLVM IR code.
    std::string llvmIr = driver.invoke();

    // Print out the resulting IR code.
    std::cout << llvmIr << std::endl;

    // Finish program.
    return 0;
}
```

#### Requirements

* [zlib](https://zlib.net/)
* [CMake >=v3.13.X](https://cmake.org/download/)
* [Python =v2.7](https://www.python.org/download/releases/2.7/)
* [Visual Studio 2019 with C++ tools (Windows)](https://visualstudio.microsoft.com/downloads/)
* [MinGW-w64 (Windows)](https://ayera.dl.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe)
* [LLVM >=v9.0.0](https://releases.llvm.org/download.html) (must build from source on Windows, see section below)

#### (Recommended) Automatically building LLVM from source (Windows)

0. Ensure you have _all_ the requirements (excluding LLVM) properly installed, as the build process for LLVM on Windows will require Python, CMake and MinGW.

1. Download sources ([Visit LLVM's downloads page](http://releases.llvm.org/download.html)) for LLVM 9.0.0 (or [click here](http://releases.llvm.org/9.0.0/llvm-9.0.0.src.tar.xz) to download them directly).

2. Extract sources onto a directory whose absolute path contains no spaces. For example, use `C:/LLVM_BUILD` instead of `C:/LLVM BUILD`. This will prevent the CMake build from failing, since it seems that a certain project has a hard time with paths with spaces.

3. Copy the `install_llvm.bat` file in this folder to the folder where you extracted the sources.

4. Run the `install_llvm.bat` file you just copied **as administrator** by right-clicking it then selecting `Run as administrator`.

#### Building LLVM from source (Windows)

0. Ensure you have _all_ the requirements (excluding LLVM) properly installed, as the build process for LLVM on Windows will require Python, CMake and MinGW.

Additionally, install the following packages using the MinGW Installation Manager if not already installed:

* `mingw32-gcc-bin`
* `mingw32-gcc-g++-bin`

1. Download sources ([Visit LLVM's downloads page](http://releases.llvm.org/download.html)) for LLVM 9.0.0 (or [click here](http://releases.llvm.org/9.0.0/llvm-9.0.0.src.tar.xz) to download them directly).

2. Extract sources onto a directory whose absolute path contains no spaces. For example, use `C:/LLVM_BUILD` instead of `C:/LLVM BUILD`. This will prevent the CMake build from failing, since it seems that a certain project has a hard time with paths with spaces.

3. Build sources using a Windows command prompt with **administrator privileges** by issuing the following commands:

```
> cd <sources directory>
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Release -DLLVM_BUILD_LLVM_DYLIB=ON -DLLVM_INCLUDE_TESTS=OFF -DLLVM_ENABLE_ZLIB=OFF
> cmake --build . --config Release --target install -j8
> cd ..
```

**First command (cmake -G ...)**

It must be specified to CMake (through `-G "MinGW Makefiles`) to use MinGW on Windows (GCC) since LLVM cannot be built by MSVC (the Visual Studio C++ Compiler), thus making MinGW a requirement in Windows.

A build directory is required by MinGW, this is why the `build` directory is created and used.

The `-j8` flag instructs CMake to use 8 parallel builds (or concurrent jobs), so as to not take up 100% CPU usage. Beware that the more jobs specified, the more RAM that may be used. Note that specifying too many jobs may cause memory exhaustion. If you feel that you have complient hardware, you may adjust this flag accordingly.

The `LLVM_BUILD_LLVM_DYLIB=ON` option will instruct the compiler to add the shared library target `libLLVM` which is required since the project is built dynamically on Windows, not statically.

The `LLVM_INCLUDE_TESTS=OFF` option will instruct CMake to omit building tests, which would conflict with the existing Google Test project on IonIR.

**Second command (cmake --build ...)**

The `--target install` option will instruct CMake to copy the resulting LLVM installation to the `C:/Program Files (x86)/LLVM` directory on Windows. This is what we're aiming for. Additionally, please note that the target name is case-sensitive, and should always be `install` (rather than `INSTALL`).

The `CMAKE_BUILD_TYPE=Release` option will instruct CMake to build the project under the `Release` configuration, instead of `Debug`, since we're going to be installing this on our local machine.

**Additional notes**

* After this, LLVM will be installed to your machine and some required include files (ex. `IntrinsicEnums.inc`) will be generated under your installation directory, (on Windows it's usually `C:\Program Files (x86)\LLVM\include`). Copy these required files onto the local git submodule directories, and you should be good to go. Skipping this step may cause include errors, as some of LLVM's header files `#include` these generated files. Additionally, you can find out which generated files are missing by simply following include errors. Below is a list of possible generated files you might have to copy over (may not be all):
    * `llvm/Config/llvm-config.h`
    * `llvm/Config/abi-breaking.h`
    * `llvm/IR/IntrinsicEnums.inc`
    * `llvm/IR/Attributes.inc`

* LLVM sources, which are exclusively compatible with CMake, shold now be ready to be included in your `CMakeLists.txt` file. See example below:

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

For additional information on building LLVM with CMake, [view the LLVM docs on building with CMake](https://llvm.org/docs/CMake.html).

#### Installing LLVM (Linux)

Please refer to [this link](http://apt.llvm.org/) for instructions on installing LLVM on Linux systems. It is recommended to use the automatic installation script provided there.

#### LLVM notes

If CMake is having a hard time finding your LLVM installation, try setting the `LLVM_DIR` environment variable to the root folder of the installation. Example: If you build LLVM from source and have it located on your Downloads folder.

#### Building project

* In Visual Studio Code, use `Clang X.0.0 for MSVC with Visual Studio Community 2019 (amd64)` as the build/compiler tool.
* When using CMake, first configure the project using `cmake --config Debug .` then build the executable using `cmake --build .`.
* Alternatively, configure the project using `cmake --config .` then build the executable with the default options using `cmake --build .`.

#### Running tests

Use the `ctest` command bundled with CMake to run tests.

Alternatively, build project & tests and run the tests executable generated.

#### Visual Studio Code notes

If intelli-sense is failing in Visual Studio Code, there may be a few reasons behind it:

* Try re-installing plugin (usually fixes the problem).
* Compile project and its dependencies in your platform (ex. avoid using WSL on Windows).
* Ensure dependencies are properly installed and have correct versions.

#### Developer notes

1. Additional tools

* [libTooling](https://clang.llvm.org/docs/LibTooling.html)
* [libClang](https://clang.llvm.org/doxygen/group__CINDEX.html)

[Click here](https://clang.llvm.org/docs/Tooling.html) for more information.

2. Recommended use of Clang/Clang++

It is recommended to use the Clang-9 compiler to build this project. You can specify the compiler to CMake using the environment variables of `CC` and `CXX` like so:

```bash
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
```

Then running CMake.

Alternatively, you can also try running:

```bash
$ sudo update-alternatives --config c++
```

Then selecting `/usr/bin/clang++`.

#### Type theory resources

1. [LEAN tutorial](https://leanprover.github.io/tutorial/tutorial.pdf)
2. [LEAN tutorial playground](https://leanprover.github.io/tutorial/)
3. [LEAN web editor](https://leanprover.github.io/live/latest/)

#### Style guide

This project adopts [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
