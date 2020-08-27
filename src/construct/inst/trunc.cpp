#include <ionir/construct/inst/trunc.h>
#include <ionir/passes/pass.h>

namespace ionir {
    TruncInst::TruncInst(TruncInstOpts opts) :
        Inst(opts.parent, InstKind::Trunc) {
        //
    }

    void TruncInst::accept(Pass &visitor) {
        // TODO: Implement.
//        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }
}
