#pragma once

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
#include <ionir/construct/pseudo/directive.h>
#include <ionir/construct/construct.h>
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

        virtual void visit(Ptr<Construct> node);

        virtual void visitChildren(Ptr<Construct> node);

        virtual void visitFunction(Ptr<Function> node);

        virtual void visitExtern(Ptr<Extern> node);

        virtual void visitBasicBlock(Ptr<BasicBlock> node);

        virtual void visitFunctionBody(Ptr<FunctionBody> node);

        virtual void visitPrototype(Ptr<Prototype> node);

        virtual void visitVarReference(Ptr<VariableRef> node);

        virtual void visitValue(Ptr<Value<>> node);

        virtual void visitIntegerValue(Ptr<IntegerValue> node);

        virtual void visitCharValue(Ptr<CharValue> node);

        virtual void visitStringValue(Ptr<StringValue> node);

        virtual void visitBooleanValue(Ptr<BooleanValue> node);

        virtual void visitInst(Ptr<Inst> node);

        virtual void visitAllocaInst(Ptr<AllocaInst> node);

        virtual void visitReturnInst(Ptr<ReturnInst> node);

        virtual void visitBranchInst(Ptr<BranchInst> node);

        virtual void visitCallInst(Ptr<CallInst> node);

        virtual void visitStoreInst(Ptr<StoreInst> node);

        virtual void visitGlobal(Ptr<Global> node);

        virtual void visitStructDecl(Ptr<StructDecl> node);

        virtual void visitType(Ptr<Type> node);

        virtual void visitIntegerType(Ptr<IntegerType> node);

        virtual void visitVoidType(Ptr<VoidType> node);

        virtual void visitModule(Ptr<Module> node);

        virtual void visitDirective(Directive node);

        virtual void visitRef(PtrRef<> node);

        virtual void visitScopeAnchor(Ptr<ScopeAnchor<>> node);

        virtual void visitRegisterAssign(Ptr<RegisterAssign> node);
    };
}
