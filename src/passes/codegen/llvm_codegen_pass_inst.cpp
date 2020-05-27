#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitAllocaInst(Ptr<AllocaInst> node) {
        this->requireBuilder();
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        /**
         * Create the LLVM-equivalent alloca instruction
         * using the buffered builder.
         */
        llvm::AllocaInst *allocaInst =
            this->builder->CreateAlloca(type, (llvm::Value *)nullptr, *node->getYieldId());

        this->addToScope(node, allocaInst);
        this->valueStack.push(allocaInst);
    }

    void LlvmCodegenPass::visitReturnInst(Ptr<ReturnInst> node) {
        this->requireBuilder();

        OptPtr<Construct> returnInstValue = node->getValue();
        llvm::ReturnInst *llvmReturnInst = nullptr;

        if (Util::hasValue(returnInstValue)) {
            llvm::Value *llvmValue = nullptr;

            // TODO: Hotfix. Clean up messy code.
            if ((*returnInstValue)->getConstructKind() == ConstructKind::Value) {
                this->visitValue((*returnInstValue)->dynamicCast<Value<>>());
                llvmValue = this->valueStack.pop();
            }
            else {
                auto ref = (*returnInstValue)->dynamicCast<Ref<>>();

                if (!ref->isResolved()) {
                    throw std::runtime_error("Return instruction's value is an unresolved reference");
                }

                auto key = *ref->getValueAs<Construct>();
                auto llvmValueFromEntities = this->findInScope(key);

                if (!llvmValueFromEntities.has_value() || *llvmValueFromEntities == nullptr) {
                    throw std::runtime_error("Could not lookup corresponding LLVM value on the symbol table");
                }

                llvmValue = *llvmValueFromEntities;
            }

            // ------

            /**
             * Create the LLVM equivalent return instruction
             * using the buffered builder.
             */
            llvmReturnInst = this->builder->CreateRet(llvmValue);
        }
        // No value was specified. Simply return void.
        else {
            llvmReturnInst = this->builder->CreateRetVoid();
        }

        this->addToScope(node, llvmReturnInst);
        this->valueStack.push(llvmReturnInst);
    }

    void LlvmCodegenPass::visitBranchInst(Ptr<BranchInst> node) {
        this->requireBuilder();

        // Visit condition.
        this->visit(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->saveBuilder();

        PtrRef<BasicBlock> bodyRef = node->getBodyRef();
        PtrRef<BasicBlock> otherwiseRef = node->getOtherwiseRef();

        // Body reference should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body reference");
        }
        // Otherwise reference should have been resolved as well at this point.
        else if (!otherwiseRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction otherwise reference");
        }

        // Visit body and otherwise references.
        this->visitBasicBlock(*bodyRef->getValue());
        this->visitBasicBlock(*otherwiseRef->getValue());

        // Pop both reference's values.
        auto *llvmBodyBlock = this->valueStack.popAs<llvm::BasicBlock>();
        auto *llvmOtherwiseBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM branch instruction.
        llvm::BranchInst *branchInst =
            this->builder->CreateCondBr(condition, llvmBodyBlock, llvmOtherwiseBlock);

        this->addToScope(node, branchInst);

        // Finally, push the resulting branch instruction onto the value stack.
        this->valueStack.push(branchInst);
    }

    void LlvmCodegenPass::visitCallInst(Ptr<CallInst> node) {
        this->requireBuilder();

        OptPtrRef<Function> callee = node->getCallee();

        // At this point, callee must have been resolved.
        if (!Util::hasValue(callee)) {
            // TODO: Use notices.
            throw std::runtime_error("Unresolved call instruction callee");
        }

        // Attempt to resolve the callee LLVM-equivalent function.
        llvm::Function* llvmCallee = this->module->getFunction(callee->get()->getId());

        // LLVM-equivalent function could not be found. Report an error.
        if (llvmCallee == nullptr) {
            throw std::runtime_error("Call instruction referenced an undefined function");
        }

        // TODO: What about arguments?
        // Otherwise, create the LLVM call instruction.
        llvm::CallInst *callInst = this->builder->CreateCall(llvmCallee);

        this->addToScope(node, callInst);
        this->valueStack.push(callInst);
    }

    void LlvmCodegenPass::visitStoreInst(Ptr<StoreInst> node) {
        this->requireBuilder();

        PtrRef<AllocaInst> target = node->getTarget();

        // The target must be resolved before LLVM code generation.
        if (!target->isResolved()) {
            throw std::runtime_error("Store instruction's target has not been resolved");
        }

        Map<Ptr<Construct>, llvm::Value *> entitiesMap = this->emittedEntities.front();
        llvm::Value *llvmTarget = entitiesMap[*target->getValue()];

        if (llvmTarget == nullptr) {
            throw std::runtime_error("Target could not be looked up in the emitted entities map");
        }

        std::string targetId = target->getId();

        this->requireFunction();
        this->visitValue(node->getValue());

        llvm::Value *llvmValue = this->valueStack.pop();

        // Create the LLVM store instruction.
        llvm::StoreInst *storeInst = this->builder->CreateStore(llvmValue, llvmTarget);

        this->addToScope(node, storeInst);

        // Finally, push the resulting branch instruction onto the value stack.
        this->valueStack.push(storeInst);
    }
}
