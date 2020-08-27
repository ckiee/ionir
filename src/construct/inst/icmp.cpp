#include <ionir/construct/inst/icmp.h>
#include <ionir/passes/pass.h>

namespace ionir {
    IcmpInst::IcmpInst(const IcmpInstOpts &opts) :
        Inst(opts.parent, InstKind::Icmp) {
        //
    }

    void IcmpInst::accept(Pass &visitor) {
        // TODO: Implement.
//        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }
}
