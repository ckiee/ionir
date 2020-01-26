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

        (*this->section->getSymbolTable())[allocaInst->getId()] = allocaInst;

        return allocaInst;
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, PtrRef<Section> body, OptPtrRef<Section> otherwise) {
        return this->make<BranchInst>(BranchInstOpts{
            this->section,
            condition,
            body,
            otherwise
        });
    }

    Ptr<ReturnInst> InstBuilder::createReturn(OptPtr<Value<>> value) {
        return this->make<ReturnInst>(ReturnInstOpts{
            this->section,
            value
        });
    }

    Ptr<CallInst> InstBuilder::createCall(Ptr<Section> section, OptPtrRef<Function> callee) {
        return this->make<CallInst>(CallInstOpts{
            this->section,
            callee
        });
    }
}
