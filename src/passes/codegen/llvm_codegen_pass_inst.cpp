#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitAllocaInst(ionshared::Ptr<AllocaInst> node) {
        this->requireBuilder();
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        /**
         * Create the LLVM-equivalent alloca instruction
         * using the buffered builder.
         */
        llvm::AllocaInst *llvmAllocaInst =
            this->getLlvmBuilder()->CreateAlloca(type, (llvm::Value *)nullptr, node->getYieldId());

        this->valueStack.push(llvmAllocaInst);
        this->symbolTable.set(node, llvmAllocaInst);
    }

    void LlvmCodegenPass::visitReturnInst(ionshared::Ptr<ReturnInst> node) {
        this->requireBuilder();

        ionshared::OptPtr<Construct> returnInstValue = node->getValue();
        llvm::ReturnInst *llvmReturnInst = nullptr;

        if (ionshared::util::hasValue(returnInstValue)) {
            llvm::Value *llvmValue = nullptr;

            // TODO: Hotfix. Clean up messy code.
            // Process the value if applicable.
            if ((*returnInstValue)->getConstructKind() == ConstructKind::Value) {
                this->visitValue((*returnInstValue)->staticCast<Value<>>());
                llvmValue = this->valueStack.pop();
            }
            // TODO: Ref<> is no longer a construct nor should be used for name resolution (name resolution occurs on Ionlang).
//            // Otherwise, it must be a reference.
//            else if ((*returnInstValue)->getConstructKind() == ConstructKind::Ref) {
//                auto ref = (*returnInstValue)->dynamicCast<Ref<>>();
//
//                if (!ref->isResolved()) {
//                    throw std::runtime_error("Return instruction's value is an unresolved reference");
//                }
//
//                auto key = *ref->getValueAs<Construct>();
//                auto llvmValueFromEntities = this->findInScope(key);
//
//                if (!llvmValueFromEntities.has_value() || *llvmValueFromEntities == nullptr) {
//                    throw std::runtime_error("Could not lookup corresponding LLVM value on the symbol table");
//                }
//
//                llvmValue = *llvmValueFromEntities;
//            }
            else {
                throw std::runtime_error("Unexpected construct as return instruction return value");
            }

            // ------

            /**
             * Create the LLVM equivalent return instruction
             * using the buffered builder.
             */
            llvmReturnInst = this->getLlvmBuilder()->CreateRet(llvmValue);
        }
        // No value was specified. Simply return void.
        else {
            llvmReturnInst = this->getLlvmBuilder()->CreateRetVoid();
        }

        this->valueStack.push(llvmReturnInst);
//        this->addToScope(node, llvmReturnInst);
    }

    void LlvmCodegenPass::visitBranchInst(ionshared::Ptr<BranchInst> node) {
        this->requireBuilder();
        this->visit(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->lockBuffers([&, this] {
            /**
             * Visit the consequent and alternative basic blocks. There's a
             * mechanism in place to prevent the blocks from being processed
             * twice, wherever they're first encountered. Then try to pop the
             * resulting value because it might not have been emitted if it was
             * processed already.
             */
            this->visitBasicBlock(node->getConsequentBasicBlock());
            this->valueStack.tryPop();
            this->visitBasicBlock(node->getAlternativeBasicBlock());
            this->valueStack.tryPop();
        });

        std::optional<llvm::BasicBlock *> llvmConsequentBasicBlock =
            this->symbolTable.find<llvm::BasicBlock>(node->getConsequentBasicBlock());

        std::optional<llvm::BasicBlock *> llvmAlternativeBasicBlock =
            this->symbolTable.find<llvm::BasicBlock>(node->getAlternativeBasicBlock());

        if (!ionshared::util::hasValue(llvmConsequentBasicBlock) || !ionshared::util::hasValue(llvmAlternativeBasicBlock)) {
            throw std::runtime_error("Emitted LLVM basic block could not be found");
        }

        // Create the LLVM conditional branch instruction.
        llvm::BranchInst *llvmBranchInst = this->getLlvmBuilder()->CreateCondBr(
            condition,
            *llvmConsequentBasicBlock,
            *llvmAlternativeBasicBlock
        );

        this->valueStack.push(llvmBranchInst);
//        this->addToScope(node, llvmBranchInst);
    }

    void LlvmCodegenPass::visitCallInst(ionshared::Ptr<CallInst> node) {
        this->requireModule();
        this->requireBuilder();

        ionshared::Ptr<Function> callee = node->getCallee();

        /**
         * The callee has not yet been visited/emitted. Visit the callee
         * at this point, as it is required to be present on the emitted
         * entities symbol table in order to emit the call instruction.
         */
        if (!this->symbolTable.contains(callee)) {
            this->lockBuffers([&, this] {
                this->visitFunction(callee);
            });

            // TODO: The function is being discarded here, but what if that function needs to be present in the stack because of the invoking method requires to pop it?
            this->valueStack.tryPop();
        }

        // Attempt to resolve the callee LLVM-equivalent function.
        llvm::Function* llvmCallee =
            (*this->buffers.llvmModule)->getFunction(callee->getPrototype()->getName());

        // LLVM-equivalent function could not be found. Report an error.
        if (llvmCallee == nullptr) {
            throw std::runtime_error("Call instruction referenced an undefined function");
        }

        std::vector<ionshared::Ptr<Construct>> args = node->getArgs();
        llvm::ArrayRef<llvm::Value *> llvmArgs = {};

        for (const auto &arg : args) {
            this->visit(arg);

            // TODO: What if an arg was a Ref? Would it have emitted a value? No.
            // TODO: Is .vec() correct? Remember . is copy.
            llvmArgs.vec().push_back(this->valueStack.pop());
        }

        // Otherwise, create the LLVM call instruction.
        llvm::CallInst *callInst =
            this->getLlvmBuilder()->CreateCall(llvmCallee, llvmArgs);

        this->valueStack.push(callInst);
//        this->addToScope(node, callInst);
    }

    void LlvmCodegenPass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        this->requireFunction();
        this->requireBuilder();

        ionshared::Ptr<AllocaInst> target = node->getTarget();

        std::optional<llvm::AllocaInst *> llvmTargetAlloca =
            this->symbolTable.find<llvm::AllocaInst>(target);

        if (!ionshared::util::hasValue(llvmTargetAlloca)) {
            throw std::runtime_error("Target could not be retrieved from the emitted entities map");
        }

        this->visitValue(node->getValue());

        llvm::Value *llvmValue = this->valueStack.pop();

        llvm::StoreInst *llvmStoreInst =
            this->getLlvmBuilder()->CreateStore(llvmValue, *llvmTargetAlloca);

        this->valueStack.push(llvmStoreInst);
//        this->addToScope(node, llvmStoreInst);
    }

    void LlvmCodegenPass::visitJumpInst(ionshared::Ptr<JumpInst> node) {
        // TODO: Check everything thoroughly. Was just left there uncompleted!
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        this->requireBuilder();

        ionshared::Ptr<BasicBlock> basicBlockTarget = node->getBasicBlockTarget();

        this->lockBuffers([&, this] {
            /**
         * Visit the basic block. A mechanism will prevent it from being
         * emitted twice. Try popping the resulting value because it might
         * be processed if it has been previously emitted.
         */
                this->visitBasicBlock(basicBlockTarget);
                this->valueStack.tryPop();
            }
        );

        std::optional<llvm::BasicBlock *> llvmBasicBlockResult =
            this->symbolTable.find<llvm::BasicBlock>(basicBlockTarget);

        if (!ionshared::util::hasValue(llvmBasicBlockResult)) {
            throw std::runtime_error("Could not find llvm block in emitted entities: " + basicBlockTarget->getName());
        }

        // Create the LLVM branch instruction (with no condition).
        llvm::BranchInst *llvmBranchInst =
            this->getLlvmBuilder()->CreateBr(*llvmBasicBlockResult);

        this->valueStack.push(llvmBranchInst);
//        this->addToScope(node, llvmBranchInst);
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------

    }
}
