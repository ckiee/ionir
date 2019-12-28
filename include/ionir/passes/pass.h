#pragma once

#include <ionir/construct/construct.h>
#include <ionir/construct/function.h>
#include <ionir/construct/reference.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/block.h>
#include <ionir/construct/type.h>
#include <ionir/construct/global.h>
#include <ionir/construct/expr/expr.h>
#include <ionir/construct/expr/binary_expr.h>
#include <ionir/construct/values/value.h>
#include <ionir/construct/values/integer.h>
#include <ionir/construct/values/char.h>
#include <ionir/construct/values/string.h>
#include <ionir/construct/values/boolean.h>
#include <ionir/construct/insts/inst.h>
#include <ionir/construct/insts/alloca.h>
#include <ionir/construct/insts/branch.h>
#include <ionir/construct/insts/return.h>
#include <ionir/construct/insts/call.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass {
    public:
        virtual void visit(Ptr<Construct> node);

        virtual void visitFunction(Ptr<Function> node);

        virtual void visitExtern(Ptr<Extern> node);

        virtual void visitSection(Ptr<Section> node);

        virtual void visitBlock(Ptr<Block> node);

        virtual void visitType(Ptr<Type> node);

        virtual void visitPrototype(Ptr<Prototype> node);

        virtual void visitReference(Ptr<Reference> node);

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

        virtual void visitGlobal(Ptr<Global> node);
    };
}
