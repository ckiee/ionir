#pragma once

#include <optional>
#include <string>
#include <vector>
#include <ionir/misc/helpers.h>
#include <ionir/misc/type_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include <ionir/llvm/llvm_block.h>
#include "pseudo/args.h"
#include "inst.h"
#include "child_construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    class FunctionBody;

    class InstBuilder;

    enum class BasicBlockKind {
        /**
         * The entry basic block of a function body.
         */
        Entry,

        /**
         * A basic block defined by the user. Can be jumped to
         * using a goto instruction.
         */
        Label,

        /**
         * A basic block which forms part of a construct. Cannot be
         * directly accessed by the user.
         */
        Internal
    };

    struct BasicBlockOpts : ChildConstructOpts<FunctionBody> {
        BasicBlockKind kind;

        std::string id;

        std::vector<Ptr<Inst>> insts = {};

        PtrSymbolTable<Inst> symbolTable = TypeFactory::makePtrSymbolTable<Inst>();
    };

    // TODO: Must be verified to contain a single terminal instruction at the end.
    class BasicBlock : public ChildConstruct<FunctionBody>, public ScopeAnchor<Inst>, public Named {
    private:
        BasicBlockKind kind;

        std::vector<Ptr<Inst>> insts;

    public:
        explicit BasicBlock(BasicBlockOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        BasicBlockKind getKind() const noexcept;

        std::vector<Ptr<Inst>> &getInsts() noexcept;

        void setInsts(std::vector<Ptr<Inst>> insts);

        void insertInst(Ptr<Inst> inst);

        uint32_t relocateInsts(BasicBlock &target, uint32_t from = 0);

        /**
         * Attempt to find the index location of an instruction.
         * Returns null if not found.
         */
        std::optional<uint32_t> locate(Ptr<Inst> inst) const;

        Ptr<InstBuilder> createBuilder();

        OptPtr<Inst> findTerminalInst() const;
    };
}
