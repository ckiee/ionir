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
