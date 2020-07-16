#pragma once

#include <string>
#include <ionir/construct/function.h>
#include <ionir/construct/function_body.h>
#include <ionir/construct/module.h>
#include "ionir/misc/inst_builder.h"

namespace ionir {
    class AstBuilder {
    private:
        Ast ast;

        ionshared::OptPtr<Module> moduleBuffer;

        ionshared::OptPtr<Function> functionBuffer;

        ionshared::OptPtr<FunctionBody> blockBuffer;

        ionshared::OptPtr<BasicBlock> basicBlockBuffer;

        ionshared::OptPtr<InstBuilder> instBuilder;

        void setBasicBlockBuffer(ionshared::OptPtr<BasicBlock> basicBlockBuffer);

    protected:
        void require(ionshared::OptPtr<Construct> construct) const;

        void requireModule() const;

        void requireFunction() const;

        void requireFunctionBody() const;

        void requireBasicBlock() const;

        void clearBuffers();

    public:
        AstBuilder();

        Ast make() const noexcept;

        AstBuilder &module(std::string id);

        AstBuilder &function(std::string id);

        AstBuilder &functionReturnType(ionshared::Ptr<Type> returnType);

        AstBuilder &instAlloca(std::string id, ionshared::Ptr<Type> type);
    };
}
