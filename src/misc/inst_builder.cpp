#include <ionir/misc/inst_builder.h>

namespace ionir {
    InstBuilder::InstBuilder(Ptr<Section> section) : section(section) {
        //
    }

    Ptr<Section> InstBuilder::getSection() const {
        return this->section;
    }

    void InstBuilder::insert(Ptr<Inst> inst) {
        this->section->getInsts().push_back(inst);
    }

    Ptr<AllocaInst> InstBuilder::createAlloca(std::string id, Ptr<Type> type) {
        Ptr<AllocaInst> allocaInst = this->make<AllocaInst>(AllocaInstOpts{
            this->section,
            id,
            type
        });

        this->section->insertInst(allocaInst);

        return allocaInst;
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, PtrRef<Section> bodySection, PtrRef<Section> otherwiseSection) {
        return this->make<BranchInst>(BranchInstOpts{
            this->section,
            condition,
            bodySection,
            otherwiseSection
        });
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, std::string bodySectionId, std::string otherwiseSectionId) {
        PtrRef<Section> bodyBlock = std::make_shared<Ref<Section>>(bodySectionId, nullptr);
        PtrRef<Section> otherwiseBlock = std::make_shared<Ref<Section>>(otherwiseSectionId, nullptr);
        Ptr<BranchInst> branchInst = this->createBranch(condition, bodyBlock, otherwiseBlock);

        bodyBlock->setOwner(branchInst);
        otherwiseBlock->setOwner(branchInst);

        return branchInst;
    }

    Ptr<ReturnInst> InstBuilder::createReturn(OptPtr<Value<>> value) {
        return this->make<ReturnInst, ReturnInstOpts>(ReturnInstOpts{
            this->section,
            value
        });
    }

    Ptr<CallInst> InstBuilder::createCall(Ptr<Section> section, OptPtrRef<Function> callee, std::optional<std::string> yieldId) {
        return this->make<CallInst>(CallInstOpts{
            this->section,
            yieldId,
            callee
        });
    }
}
