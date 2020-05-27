#pragma once

#include <optional>
#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/construct/value/integer.h>
#include <ionir/construct/value/char.h>
#include <ionir/construct/value/string.h>
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
#include <ionir/passes/pass.h>

namespace ionir {
    class LlvmCodegenPass : public Pass {
    private:
        llvm::LLVMContext *context;

        llvm::Module *module;

        LlvmStack<llvm::Value> valueStack;

        LlvmStack<llvm::Type> typeStack;

        std::optional<llvm::Function *> function;

        std::optional<llvm::IRBuilder<>> builder;

        std::optional<llvm::BasicBlock *> block;

        std::map<std::string, llvm::Value *> namedValues;

        Stack<llvm::IRBuilder<>> builderTracker;

        ScopeList<Ptr<Construct>, llvm::Value *> emittedEntities;

        /**
         * Ensure that the builder is instantiated, otherwise
         * throws a runtime error.
         */
        void requireBuilder();

        void requireFunction();

        /**
         * Set the currently active builder if any. Modifying the builder
         * will also set/update the active LLVM basic block buffer.
         */
        void setBuilder(llvm::BasicBlock *block);

        bool saveBuilder();

        bool restoreBuilder();

        void createScope();

        void destroyScope();

        void addToScope(Ptr<Construct> construct, llvm::Value *value);

        std::optional<llvm::Value *> findInScope(Ptr<Construct> key);

    public:
        explicit LlvmCodegenPass(llvm::Module *module);

        ~LlvmCodegenPass();

        llvm::Module *getModule() const;

        LlvmStack<llvm::Value> getValueStack() const;

        LlvmStack<llvm::Type> getTypeStack() const;

        void visit(Ptr<Construct> node) override;

        void visitScopeAnchor(Ptr<ScopeAnchor<>> node) override;

        void visitFunction(Ptr<Function> node) override;

        void visitExtern(Ptr<Extern> node) override;

        void visitBasicBlock(Ptr<BasicBlock> node) override;

        void visitFunctionBody(Ptr<FunctionBody> node) override;

        void visitPrototype(Ptr<Prototype> node) override;

        void visitIntegerValue(Ptr<IntegerValue> node) override;

        void visitCharValue(Ptr<CharValue> node) override;

        void visitStringValue(Ptr<StringValue> node) override;

        void visitBooleanValue(Ptr<BooleanValue> node) override;

        void visitAllocaInst(Ptr<AllocaInst> node) override;

        void visitReturnInst(Ptr<ReturnInst> node) override;

        void visitBranchInst(Ptr<BranchInst> node) override;

        void visitCallInst(Ptr<CallInst> node) override;

        void visitStoreInst(Ptr<StoreInst> node) override;

        void visitGlobal(Ptr<Global> node) override;

        void visitType(Ptr<Type> node) override;

        void visitIntegerType(Ptr<IntegerType> node) override;

        void visitVoidType(Ptr<VoidType> node) override;

        void visitModule(Ptr<Module> node) override;
    };
}
