#include <string>
#include <ionir/construct/section.h>
#include <ionir/passes/semantic/entry_point_check_pass.h>

namespace ionir {
    void EntryPointCheckPass::visitInst(Ptr<Inst> node) {
        Pass::visitInst(node);

        // TODO
    }
}
