#pragma once

#include <optional>
#include <vector>
#include <functional>
#include <ionir/misc/helpers.h>
#include <ionir/misc/type_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include "ionir/construct/pseudo/child_construct.h"
#include "basic_block.h"

namespace ionir {
    class Pass;

    class Function;

    class FunctionBody : public ChildConstruct<Function>, public ScopeAnchor<BasicBlock> {
    public:
        explicit FunctionBody(ionshared::Ptr<Function> parent, PtrSymbolTable<BasicBlock> symbolTable = ionshared::Util::makePtrSymbolTable<BasicBlock>());

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        bool verify() override;

        ionshared::OptPtr<BasicBlock> findEntryBasicBlock();

        bool hasEntryBasicBlock();

        void insertBasicBlock(ionshared::Ptr<BasicBlock> basicBlock);
    };
}
