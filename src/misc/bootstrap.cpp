#include <ionir/const/const_name.h>
#include <ionir/misc/ast_builder.h>
#include <ionir/misc/bootstrap.h>

namespace ionir {
    Ast Bootstrap::functionAst(std::string id) {
        return AstBuilder()
            .module(ConstName::anonymous)
            .function(id)
            .getAst();
    }

    Ptr<Function> Bootstrap::function(std::string id) {
        Ptr<Module> module = Bootstrap::functionAst(id)[0]->cast<Module>();

        return (*module->getSymbolTable())[id]->cast<Function>();
    }
}
