#include <ionir/syntax/ast_printer.h>
#include <ionir/misc/bootstrap.h>
#include "pch.h"

using namespace ionir;

TEST(AstPrinter, GetString) {
    Ast ast = Bootstrap::functionAst();
    AstPrinter astPrinter = AstPrinter(ast);
    std::optional<std::string> astString = astPrinter.make();

    if (astString.has_value()) {
        std::cout << "Printer result: \n" << *astString << std::endl;
    }
    else {
        std::cout << "Printer has no result." << std::endl;
    }
}
