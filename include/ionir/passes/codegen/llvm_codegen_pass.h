#pragma once

#include <optional>
#include <stack>
#include <queue>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/construct/value/integer_value.h>
#include <ionir/construct/value/char_value.h>
#include <ionir/construct/value/string_value.h>
#include <ionir/construct/inst.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/construct.h>
#include <ionir/construct/function.h>
#include <ionir/construct/type.h>
#include <ionir/construct/function_body.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/global.h>
#include <ionir/container/llvm_stack.h>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/context.h>
#include <ionir/passes/pass.h>

namespace ionir {
    class LlvmCodegenPass : public Pass {
    private:
        ionshared::Ptr<Context> contextBuffer;

        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules;

        LlvmStack<llvm::Value> valueStack;

        LlvmStack<llvm::Type> typeStack;

        std::queue<std::string> registerQueue;

        /**
         * The currently active LLVM context;
         */
        std::optional<llvm::LLVMContext *> llvmContextBuffer;

        /**
         * The currently active LLVM module.
         */
        std::optional<llvm::Module *> llvmModuleBuffer;

        std::optional<llvm::Function *> llvmFunctionBuffer;

        std::optional<llvm::IRBuilder<>> llvmBuilderBuffer;

        std::optional<llvm::BasicBlock *> llvmBasicBlockBuffer;

        std::map<std::string, llvm::Value *> namedValues;

        Stack<llvm::IRBuilder<>> builderTracker;

        ScopeList<ionshared::Ptr<Construct>, llvm::Value *> emittedEntities;

        /**
         * Ensure that the builder is instantiated, otherwise throws
         * a runtime error.
         */
        void requireBuilder();

        void requireFunction();

        void requireModule();

        void requireContext();

        /**
         * Set the currently active builder if any. Modifying the builder
         * will also set/update the active LLVM basic block buffer.
         */
        void setBuilder(llvm::BasicBlock *basicBlock);

        bool saveBuilder();

        bool restoreBuilder();

        void resetContextBuffer() noexcept;

        std::optional<llvm::Value *> findInScope(ionshared::Ptr<Construct> key);

    public:
        explicit LlvmCodegenPass(
            ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules =
                std::make_shared<ionshared::SymbolTable<llvm::Module *>>()
        );

        ~LlvmCodegenPass();

        [[nodiscard]] ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> getModules() const;

        [[nodiscard]] LlvmStack<llvm::Value> getValueStack() const noexcept;

        [[nodiscard]] LlvmStack<llvm::Type> getTypeStack() const noexcept;

        [[nodiscard]] std::queue<std::string> getRegisterQueue() const noexcept;

        [[nodiscard]] std::optional<llvm::Module *> getModuleBuffer() const;

        bool setModuleBuffer(const std::string &id);

        void visit(ionshared::Ptr<Construct> node) override;

        void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) override;

        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitExtern(ionshared::Ptr<Extern> node) override;

        void visitBasicBlock(ionshared::Ptr<BasicBlock> node) override;

        void visitFunctionBody(ionshared::Ptr<FunctionBody> node) override;

        void visitPrototype(ionshared::Ptr<Prototype> node) override;

        void visitIntegerValue(ionshared::Ptr<IntegerValue> node) override;

        void visitCharValue(ionshared::Ptr<CharValue> node) override;

        void visitStringValue(ionshared::Ptr<StringValue> node) override;

        void visitBooleanValue(ionshared::Ptr<BooleanValue> node) override;

        void visitAllocaInst(ionshared::Ptr<AllocaInst> node) override;

        void visitReturnInst(ionshared::Ptr<ReturnInst> node) override;

        void visitBranchInst(ionshared::Ptr<BranchInst> node) override;

        void visitCallInst(ionshared::Ptr<CallInst> node) override;

        void visitStoreInst(ionshared::Ptr<StoreInst> node) override;

        void visitJumpInst(ionshared::Ptr<JumpInst> node) override;

        void visitGlobal(ionshared::Ptr<Global> node) override;

        void visitType(ionshared::Ptr<Type> node) override;

        void visitIntegerType(ionshared::Ptr<IntegerType> node) override;

        void visitBooleanType(ionshared::Ptr<BooleanType> node) override;

        void visitVoidType(ionshared::Ptr<VoidType> node) override;

        void visitModule(ionshared::Ptr<Module> node) override;

        void visitRegisterAssign(ionshared::Ptr<RegisterAssign> node) override;
    };
}
