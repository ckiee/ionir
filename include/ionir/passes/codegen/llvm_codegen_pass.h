#pragma once

#include <optional>
#include <stack>
#include <queue>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <ionshared/container/llvm_stack.h>
#include <ionir/construct/value/integer_literal.h>
#include <ionir/construct/value/char_literal.h>
#include <ionir/construct/value/string_literal.h>
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
#include <ionir/tracking/context.h>
#include <ionir/llvm/llvm_emitted_entities.h>
#include <ionir/passes/pass.h>

namespace ionir {
    class LlvmCodegenPass : public Pass {
    private:
        /**
         * The context buffer is always set. It's constructed as an
         * independent, empty context, with an empty global scope and
         * no other scopes.
         */
        ionshared::Ptr<Context> contextBuffer;

        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules;

        ionshared::LlvmStack<llvm::Value> valueStack;

        ionshared::LlvmStack<llvm::Type> typeStack;

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

        ionshared::Stack<llvm::IRBuilder<>> builderTracker;

        LlvmEmittedEntities emittedEntities;

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

        void lockBuilder(const std::function<void()> &callback);

    public:
        IONSHARED_PASS_ID;

        explicit LlvmCodegenPass(
            ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules =
                std::make_shared<ionshared::SymbolTable<llvm::Module *>>()
        );

        ~LlvmCodegenPass();

        [[nodiscard]] ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> getModules() const;

        [[nodiscard]] ionshared::LlvmStack<llvm::Value> getValueStack() const noexcept;

        [[nodiscard]] ionshared::LlvmStack<llvm::Type> getTypeStack() const noexcept;

        [[nodiscard]] std::optional<llvm::Module *> getModuleBuffer() const;

        bool setModuleBuffer(const std::string &id);

        void visit(ionshared::Ptr<Construct> node) override;

        void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) override;

        void visitFunction(ionshared::Ptr<Function> node) override;

        void visitExtern(ionshared::Ptr<Extern> node) override;

        void visitBasicBlock(ionshared::Ptr<BasicBlock> node) override;

        void visitFunctionBody(ionshared::Ptr<FunctionBody> node) override;

        void visitPrototype(ionshared::Ptr<Prototype> node) override;

        void visitIntegerLiteral(ionshared::Ptr<IntegerLiteral> node) override;

        void visitCharLiteral(ionshared::Ptr<CharLiteral> node) override;

        void visitStringLiteral(ionshared::Ptr<StringLiteral> node) override;

        void visitBooleanLiteral(ionshared::Ptr<BooleanLiteral> node) override;

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
    };
}
