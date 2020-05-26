#include <ionir/const/const_name.h>
#include <ionir/syntax/ast_builder.h>
#include <ionir/misc/bootstrap.h>

namespace ionir {
    Ast Bootstrap::functionAst(std::string id) {
        return AstBuilder()
            .module(ConstName::anonymous)
            .function(id)
            .make();
    }

    Ptr<Function> Bootstrap::function(std::string id) {
        Ptr<Module> module = Bootstrap::functionAst(id)[0]->dynamicCast<Module>();

        return (*module->getSymbolTable())[id]->dynamicCast<Function>();
    }

    Ptr<BasicBlock> Bootstrap::basicBlock(Ptr<FunctionBody> parent, std::string id, BasicBlockKind basicBlockKind) {
        return std::make_shared<BasicBlock>(BasicBlockOpts{
            parent,
            basicBlockKind,
            id
        });
    }
}
