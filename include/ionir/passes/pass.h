#pragma once

#include <ionir/construct/expr/binary_expr.h>
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
#include <ionir/construct/type/variable_decl.h>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
#include <ionir/construct/pseudo/directive.h>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/construct/construct.h>
#include <ionir/construct/function.h>
#include <ionir/construct/variable_ref.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/block.h>
#include <ionir/construct/type.h>
#include <ionir/construct/global.h>
#include <ionir/construct/module.h>
#include <ionir/construct/expr.h>
#include <ionir/construct/value.h>
#include <ionir/construct/inst.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass {
    public:
        virtual void visit(Ptr<Construct> node);

        virtual void visitFunction(Ptr<Function> node);

        virtual void visitExtern(Ptr<Extern> node);

        virtual void visitSection(Ptr<Section> node);

        virtual void visitBlock(Ptr<Block> node);

        virtual void visitPrototype(Ptr<Prototype> node);

        virtual void visitVarReference(Ptr<VariableRef> node);

        virtual void visitExpr(Ptr<Expr> node);

        virtual void visitBinaryExpr(Ptr<BinaryExpr> node);

        virtual void visitValue(Ptr<Value> node);

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

        virtual void visitVariableDecl(Ptr<VariableDecl> node);

        virtual void visitType(Ptr<Type> node);

        virtual void visitIntegerType(Ptr<IntegerType> node);

        virtual void visitVoidType(Ptr<VoidType> node);

        virtual void visitModule(Ptr<Module> node);

        virtual void visitDirective(Directive node);

        virtual void visitRef(PtrRef<> node);
    };
}
