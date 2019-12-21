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
    return this->make<AllocaInst>(AllocaInstOpts{
        this->section,
        id,
        type,
    });
}

Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise)
{
    return this->make<BranchInst>(BranchInstOpts{
        this->section,
        condition,
        body,
        otherwise,
    });
}

Ptr<ReturnInst> InstBuilder::createReturn(std::optional<Ptr<Value>> value)
{
    return this->make<ReturnInst>(ReturnInstOpts{
        this->section,
        value,
    });
}

Ptr<CallInst> InstBuilder::createCall(Ptr<Section> section, std::string target, std::optional<Ptr<Function>> callee)
{
    return this->make<CallInst>(CallInstOpts{
        this->section,
        target,
        callee,
    });
}
} // namespace ionir
