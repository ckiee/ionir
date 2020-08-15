#include <ionir/construct/inst/zext.h>
#include <ionir/passes/pass.h>

namespace ionir {
    ZextInst::ZextInst(ZextInstOpts opts) : Inst(opts.parent, InstKind::Zext) {
        //
    }

    void ZextInst::accept(Pass &visitor) {
        // TODO: Implement.
//        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }
}
