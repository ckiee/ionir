#pragma once

#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    class Function;

    struct PtrToIntInstOpts : InstOpts {
        // TODO
    };

    class PtrToIntInst : public Inst {
    public:
        explicit PtrToIntInst(const PtrToIntInstOpts &opts);

        void accept(Pass &visitor) override;
    };
}
