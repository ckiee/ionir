#pragma once

#include <optional>
#include <string>
#include <vector>
#include <ionir/misc/helpers.h>
#include <ionir/misc/type_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include "pseudo/args.h"
#include "inst.h"
#include "ionir/construct/pseudo/child_construct.h"
#include "type.h"
#include "register_assign.h"

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

        std::vector<ionshared::Ptr<RegisterAssign>> registers = {};

        std::vector<ionshared::Ptr<Inst>> insts = {};

        PtrSymbolTable<Inst> symbolTable = ionshared::Util::makePtrSymbolTable<Inst>();
    };

    // TODO: Must be verified to contain a single terminal instruction at the end.
    class BasicBlock : public ChildConstruct<FunctionBody>, public ScopeAnchor<Inst>, public ionshared::Named {
    private:
        BasicBlockKind kind;

        std::vector<ionshared::Ptr<RegisterAssign>> registers;

        std::vector<ionshared::Ptr<Inst>> insts;

    public:
        explicit BasicBlock(const BasicBlockOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        BasicBlockKind getKind() const noexcept;

        std::vector<ionshared::Ptr<RegisterAssign>> &getRegisters() noexcept;

        void setRegisters(std::vector<ionshared::Ptr<RegisterAssign>> registers);

        std::vector<ionshared::Ptr<Inst>> &getInsts() noexcept;

        void setInsts(std::vector<ionshared::Ptr<Inst>> insts);

        void insertInst(const ionshared::Ptr<Inst> &inst);

        uint32_t relocateInsts(BasicBlock &target, uint32_t from = 0);

        /**
         * Attempt to find the index location of an instruction.
         * Returns null if not found.
         */
        std::optional<uint32_t> locate(ionshared::Ptr<Inst> inst) const;

        ionshared::Ptr<InstBuilder> createBuilder();

        ionshared::OptPtr<Inst> findTerminalInst() const;
    };
}