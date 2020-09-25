#pragma once

#include <optional>
#include <vector>
#include <functional>
#include <ionir/misc/type_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include "ionir/construct/pseudo/child_construct.h"
#include "basic_block.h"

namespace ionir {
    class Pass;

    class Function;

    struct FunctionBody : public ChildConstruct<Function>, public ScopeAnchor<BasicBlock> {
        explicit FunctionBody(
            ionshared::Ptr<Function> parent,

            PtrSymbolTable<BasicBlock> symbolTable =
                ionshared::util::makePtrSymbolTable<BasicBlock>()
        );

        void accept(Pass &visitor) override;

        Ast getChildrenNodes() override;

        bool verify() override;

        [[nodiscard]] ionshared::OptPtr<BasicBlock> findEntryBasicBlock();

        [[nodiscard]] bool hasEntryBasicBlock();

        void insertBasicBlock(const ionshared::Ptr<BasicBlock> &basicBlock);
    };
}
