#pragma once

#include "ast_nodes/inst.h"
#include "ast_nodes/section.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/branch.h"
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/insts/return.h"
#include "ast_nodes/insts/call.h"
#include "misc/helpers.h"

namespace ionir
{
class InstBuilder
{
protected:
    Ptr<Section> section;

public:
    InstBuilder(Ptr<Section> section);

    Ptr<Section> getSection() const;

    void insert(Ptr<Inst> inst);

    template <class TInst, typename... TArgs>
    Ptr<TInst> make(TArgs... args)
    {
        // TODO: Ensure T inherits from Inst or derived.

        Ptr<TInst> inst = std::make_shared<TInst>(args);

        this->insert(inst);

        return inst;
    }

    Ptr<AllocaInst> createAlloca(std::string id, Ptr<Type> type);

    Ptr<BranchInst> createBranch(Ptr<BinaryExpr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise = std::nullopt);

    Ptr<GotoInst> createGoto(Ptr<Scope> scope, std::string target, std::optional<Ptr<Section>> section = std::nullopt);

    Ptr<ReturnInst> createReturn(std::optional<Ptr<Value>> value = std::nullopt);

    Ptr<CallInst> createCall(Ptr<Scope> scope, std::string target, std::optional<Ptr<Function>> callee = std::nullopt);
};
} // namespace ionir
