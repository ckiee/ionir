#pragma once

#include <ionshared/passes/base_pass.h>
#include <ionshared/passes/base_pass_manager.h>
#include <ionir/construct/construct.h>
#include <ionir/construct/value/integer_literal.h>
#include <ionir/construct/value/char_literal.h>
#include <ionir/construct/value/string_literal.h>
#include <ionir/construct/value/boolean_literal.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/store.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/inst/jump.h>
#include <ionir/construct/type/struct_decl.h>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
#include <ionir/construct/type/boolean_type.h>
#include <ionir/construct/type/pointer_type.h>
#include <ionir/construct/pseudo/directive.h>
#include <ionir/construct/pseudo/error_marker.h>
#include <ionir/construct/function.h>
#include <ionir/construct/variable_ref.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/function_body.h>
#include <ionir/construct/type.h>
#include <ionir/construct/global.h>
#include <ionir/construct/module.h>
#include <ionir/construct/value.h>
#include <ionir/construct/inst.h>
#include "pass_context.h"

#define IONIR_PASS_INTERNAL_ASSERT(condition) if (!this->getContext().getDiagnosticBuilder()->internalAssert(condition)) { return; }

namespace ionir {
    class Pass : public ionshared::BasePass<Construct> {
    private:
        PassContext context;

    public:
        explicit Pass(PassContext context);

        [[nodiscard]] PassContext getContext() const noexcept;

        void visit(ionshared::Ptr<Construct> node) override;

        virtual void visitChildren(ionshared::Ptr<Construct> node);

        virtual void visitFunction(ionshared::Ptr<Function> node);

        virtual void visitExtern(ionshared::Ptr<Extern> node);

        virtual void visitBasicBlock(ionshared::Ptr<BasicBlock> node);

        virtual void visitFunctionBody(ionshared::Ptr<FunctionBody> node);

        virtual void visitPrototype(ionshared::Ptr<Prototype> node);

        virtual void visitVarReference(ionshared::Ptr<VariableRef> node);

        virtual void visitValue(ionshared::Ptr<Value<>> node);

        virtual void visitIntegerLiteral(ionshared::Ptr<IntegerLiteral> node);

        virtual void visitCharLiteral(ionshared::Ptr<CharLiteral> node);

        virtual void visitStringLiteral(ionshared::Ptr<StringLiteral> node);

        virtual void visitBooleanLiteral(ionshared::Ptr<BooleanLiteral> node);

        virtual void visitInst(ionshared::Ptr<Inst> node);

        virtual void visitAllocaInst(ionshared::Ptr<AllocaInst> node);

        virtual void visitReturnInst(ionshared::Ptr<ReturnInst> node);

        virtual void visitBranchInst(ionshared::Ptr<BranchInst> node);

        virtual void visitCallInst(ionshared::Ptr<CallInst> node);

        virtual void visitStoreInst(ionshared::Ptr<StoreInst> node);

        virtual void visitJumpInst(ionshared::Ptr<JumpInst> node);

        virtual void visitGlobal(ionshared::Ptr<Global> node);

        virtual void visitStructDecl(ionshared::Ptr<StructDecl> node);

        virtual void visitType(ionshared::Ptr<Type> node);

        virtual void visitIntegerType(ionshared::Ptr<IntegerType> node);

        virtual void visitVoidType(ionshared::Ptr<VoidType> node);

        virtual void visitBooleanType(ionshared::Ptr<BooleanType> node);

        virtual void visitPointerType(ionshared::Ptr<PointerType> node);

        virtual void visitModule(ionshared::Ptr<Module> node);

        virtual void visitDirective(Directive node);

        virtual void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node);

        virtual void visitErrorMarker(ionshared::Ptr<ErrorMarker> node);
    };

    typedef ionshared::BasePassManager<Pass, Construct> PassManager;
}
