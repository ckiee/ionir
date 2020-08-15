#include <ionir/const/const_name.h>
#include <ionir/syntax/ast_builder.h>
#include <ionir/misc/bootstrap.h>

namespace ionir {
    Ast Bootstrap::functionAst(std::string id) {
        return AstBuilder()
            .module(ConstName::anonymous)
            .function(std::move(id))
            .make();
    }

    ionshared::Ptr<Function> Bootstrap::function(const std::string &id) {
        ionshared::Ptr<Module> module = Bootstrap::functionAst(id)[0]->dynamicCast<Module>();

        return (*module->getSymbolTable())[id]->dynamicCast<Function>();
    }

    ionshared::Ptr<BasicBlock> Bootstrap::basicBlock(ionshared::Ptr<FunctionBody> parent, std::string id, BasicBlockKind basicBlockKind) {
        return std::make_shared<BasicBlock>(BasicBlockOpts{
            std::move(parent),
            basicBlockKind,
            std::move(id)
        });
    }
}
