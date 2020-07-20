#pragma once

#include <ionshared/passes/pass_manager.h>
#include <ionir/construct/construct.h>
#include <ionir/construct/value/integer.h>
#include <ionir/construct/value/char.h>
#include <ionir/construct/value/string.h>
#include <ionir/construct/value/boolean.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/store.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/type/struct_decl.h>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
#include <ionir/construct/type/boolean_type.h>
#include <ionir/construct/pseudo/directive.h>
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
#include <ionir/construct/register_assign.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass {
    public:
        /**
         * Invoked when the pass is about to process the AST.
         */
        virtual void prepare();

        /**
         * Invoked when the pass has traversed the entire AST.
         */
        virtual void finish();

        virtual void visit(ionshared::Ptr<Construct> node);

        virtual void visitChildren(ionshared::Ptr<Construct> node);

        virtual void visitFunction(ionshared::Ptr<Function> node);

        virtual void visitExtern(ionshared::Ptr<Extern> node);

        virtual void visitBasicBlock(ionshared::Ptr<BasicBlock> node);

        virtual void visitFunctionBody(ionshared::Ptr<FunctionBody> node);

        virtual void visitPrototype(ionshared::Ptr<Prototype> node);

        virtual void visitVarReference(ionshared::Ptr<VariableRef> node);

        virtual void visitValue(ionshared::Ptr<Value<>> node);

        virtual void visitIntegerValue(ionshared::Ptr<IntegerValue> node);

        virtual void visitCharValue(ionshared::Ptr<CharValue> node);

        virtual void visitStringValue(ionshared::Ptr<StringValue> node);

        virtual void visitBooleanValue(ionshared::Ptr<BooleanValue> node);

        virtual void visitInst(ionshared::Ptr<Inst> node);

        virtual void visitAllocaInst(ionshared::Ptr<AllocaInst> node);

        virtual void visitReturnInst(ionshared::Ptr<ReturnInst> node);

        virtual void visitBranchInst(ionshared::Ptr<BranchInst> node);

        virtual void visitCallInst(ionshared::Ptr<CallInst> node);

        virtual void visitStoreInst(ionshared::Ptr<StoreInst> node);

        virtual void visitGlobal(ionshared::Ptr<Global> node);

        virtual void visitStructDecl(ionshared::Ptr<StructDecl> node);

        virtual void visitType(ionshared::Ptr<Type> node);

        virtual void visitIntegerType(ionshared::Ptr<IntegerType> node);

        virtual void visitVoidType(ionshared::Ptr<VoidType> node);

        virtual void visitBooleanType(ionshared::Ptr<BooleanType> node);

        virtual void visitModule(ionshared::Ptr<Module> node);

        virtual void visitDirective(Directive node);

        virtual void visitRef(PtrRef<> node);

        virtual void visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node);

        virtual void visitRegisterAssign(ionshared::Ptr<RegisterAssign> node);
    };

    typedef ionshared::BarePassManager<Pass, Construct> PassManager;

    typedef ionshared::PassManagerItem<Pass> PassManagerItem;
}
