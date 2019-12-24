#pragma once

#include "construct/construct.h"
#include "construct/function.h"
#include "construct/reference.h"
#include "construct/prototype.h"
#include "construct/extern.h"
#include "construct/block.h"
#include "construct/type.h"
#include "construct/global.h"
#include "construct/expr/expr.h"
#include "construct/expr/binary_expr.h"
#include "construct/values/value.h"
#include "construct/values/integer.h"
#include "construct/values/char.h"
#include "construct/values/string.h"
#include "construct/values/boolean.h"
#include "construct/insts/inst.h"
#include "construct/insts/alloca.h"
#include "construct/insts/branch.h"
#include "construct/insts/return.h"
#include "construct/insts/call.h"
#include "misc/helpers.h"

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
