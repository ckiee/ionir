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
#include <ionir/passes/pass.h>

namespace ionir {
    class LlvmCodegenPass : public Pass {
    private:
        LlvmStack<llvm::Value> valueStack;

        LlvmStack<llvm::Type> typeStack;

        std::queue<std::string> registerQueue;

        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules;

        /**
         * The currently active LLVM context;
         */
        std::optional<llvm::LLVMContext *> contextBuffer;

        /**
         * The currently active LLVM module.
         */
        std::optional<llvm::Module *> moduleBuffer;

        std::optional<llvm::Function *> functionBuffer;

        std::optional<llvm::IRBuilder<>> builderBuffer;

        std::optional<llvm::BasicBlock *> blockBuffer;

        std::map<std::string, llvm::Value *> namedValues;

        Stack<llvm::IRBuilder<>> builderTracker;

        ScopeList<ionshared::Ptr<Construct>, llvm::Value *> emittedEntities;

        /**
         * Ensure that the builder is instantiated, otherwise
         * throws a runtime error.
         */
        void requireBuilder();

        void requireFunction();

        void requireModule();

        void requireContext();

        /**
         * Set the currently active builder if any. Modifying the builder
         * will also set/update the active LLVM basic block buffer.
         */
        void setBuilder(llvm::BasicBlock *block);

        bool saveBuilder();

        bool restoreBuilder();

        void createScope();

        void destroyScope();

        void addToScope(ionshared::Ptr<Construct> construct, llvm::Value *value);

        std::optional<llvm::Value *> findInScope(ionshared::Ptr<Construct> key);

    public:
        explicit LlvmCodegenPass(
            ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules =
                std::make_shared<ionshared::SymbolTable<llvm::Module *>>()
        );

        ~LlvmCodegenPass();

        LlvmStack<llvm::Value> getValueStack() const noexcept;

        LlvmStack<llvm::Type> getTypeStack() const noexcept;

        std::queue<std::string> getRegisterQueue() const noexcept;

        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> getModules() const;

        std::optional<llvm::Module *> getModuleBuffer() const;

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

        void visitGlobal(ionshared::Ptr<Global> node) override;

        void visitType(ionshared::Ptr<Type> node) override;

        void visitIntegerType(ionshared::Ptr<IntegerType> node) override;

        void visitVoidType(ionshared::Ptr<VoidType> node) override;

        void visitModule(ionshared::Ptr<Module> node) override;

        void visitRegisterAssign(ionshared::Ptr<RegisterAssign> node) override;
    };
}
