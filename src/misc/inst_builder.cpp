#include "inst_builder.h"

namespace ionir
{
InstBuilder::InstBuilder(Ptr<Section> section) : section(section)
{
    //
}

Ptr<Section> InstBuilder::getSection() const
{
    return this->section;
}

void InstBuilder::insert(Ptr<Inst> inst)
{
    this->section->getInsts().push_back(inst);
}

Ptr<AllocaInst> InstBuilder::createAlloca(std::string id, Ptr<Type> type)
{
    return this->make<AllocaInst>(id, type);
}

Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise)
{
    return this->make<BranchInst>(condition, body, otherwise);
}

Ptr<GotoInst> InstBuilder::createGoto(Ptr<Scope> scope, std::string target, std::optional<Ptr<Section>> section)
{
    return this->make<GotoInst>(scope, target, section);
}

Ptr<ReturnInst> InstBuilder::createReturn(std::optional<Ptr<Value>> value)
{
    return this->make<ReturnInst>(value);
}

Ptr<CallInst> InstBuilder::createCall(Ptr<Scope> scope, std::string target, std::optional<Ptr<Function>> callee)
{
    return this->make<CallInst>(scope, target, callee);
}
} // namespace ionir
