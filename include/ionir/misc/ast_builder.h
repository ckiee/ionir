#pragma once

#include <string>
#include <ionir/construct/function.h>
#include <ionir/construct/block.h>
#include <ionir/construct/module.h>
#include "inst_builder.h"

namespace ionir {
    class AstBuilder : std::enable_shared_from_this<AstBuilder> {
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
        static Ptr<AstBuilder> make();

        AstBuilder();

        Ast getAst() const;

        Ptr<AstBuilder> module(std::string id);

        Ptr<AstBuilder> function(std::string id);

        Ptr<AstBuilder> functionReturnType(Ptr<Type> returnType);

        Ptr<AstBuilder> instAlloca(std::string id, Ptr<Type> type);
    };
}
