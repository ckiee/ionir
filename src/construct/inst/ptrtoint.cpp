#include <ionir/construct/inst/ptrtoint.h>
#include <ionir/passes/pass.h>

namespace ionir {
    PtrToIntInst::PtrToIntInst(PtrToIntInstOpts opts)
        : Inst(opts.parent, InstKind::Call) {
        //
    }

    void CallInst::accept(Pass &visitor) {
        // TODO: Implement.
//        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }
}
