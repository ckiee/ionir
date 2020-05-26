#pragma once

#include <optional>
#include <vector>
#include <functional>
#include <ionir/misc/helpers.h>
#include <ionir/misc/type_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include "child_construct.h"
#include "basic_block.h"

namespace ionir {
    class Pass;

    class Function;

    class FunctionBody : public ChildConstruct<Function>, public ScopeAnchor<BasicBlock> {
    public:
        explicit FunctionBody(Ptr<Function> parent, PtrSymbolTable<BasicBlock> symbolTable = TypeFactory::makePtrSymbolTable<BasicBlock>());

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        bool verify() override;

        OptPtr<BasicBlock> findEntryBasicBlock();

        bool hasEntryBasicBlock();

        void insertBasicBlock(Ptr<BasicBlock> basicBlock);
    };
}
