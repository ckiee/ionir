#pragma once

#include <string>
#include <ionir/construct/function.h>
#include <ionir/construct/block.h>
#include <ionir/construct/module.h>
#include "ionir/misc/inst_builder.h"

namespace ionir {
    class AstBuilder {
    private:
        Ast ast;

        OptPtr<Module> moduleBuffer;

        OptPtr<Function> functionBuffer;

        OptPtr<Block> blockBuffer;

        OptPtr<Section> sectionBuffer;

        OptPtr<InstBuilder> instBuilder;

        void setSectionBuffer(OptPtr<Section> sectionBuffer);

    protected:
        void require(OptPtr<Construct> construct) const;

        void requireModule() const;

        void requireFunction() const;

        void requireBlock() const;

        void requireSection() const;

        void clearBuffers();

    public:
        AstBuilder();

        Ast make() const noexcept;

        AstBuilder &module(std::string id);

        AstBuilder &function(std::string id);

        AstBuilder &functionReturnType(Ptr<Type> returnType);

        AstBuilder &instAlloca(std::string id, Ptr<Type> type);
    };
}
