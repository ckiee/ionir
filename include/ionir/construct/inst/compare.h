#pragma once

#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    class Function;

    struct IcmpInstOpts : InstOpts {
        // TODO
    };

    struct CompareInst : Inst {
        explicit CompareInst(const IcmpInstOpts &opts);

        void accept(Pass &visitor) override;
    };
}
