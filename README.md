#### Getting started

Prepare the project, initialize and update required Git submodules:

```shell
$ make prepare
```

Then, you'd want to invoke the Makefile to automatically build and compile the project:

```shell
$ make
```

#### Usage

A general usage example is provided below.

```cpp
#include "Generation/Driver.hpp"
#include "Syntax/Lexer.hpp"
#include "Syntax/Stream.hpp"
#include "Syntax/Token.hpp"

using namespace std;

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
* Python =2.7
* Visual Studio 2019 with C++ Tools
* LLVM >=v9.0.0 (must build from source, see section below)

#### Building LLVM

1. Download and extract sources.

2. Build sources using a Windows command prompt with administrator privileges.

```
> cd <sources directory>
> cmake .
> cmake --build . --config Release --target INSTALL
```

3. Use `Clang X.0.0 for MSVC with Visual Studio Community 2019 (amd64)` as the build/compiler tool.

#### Style Guide

This project adopts [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
