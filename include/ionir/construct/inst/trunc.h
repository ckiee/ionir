#pragma once

#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    class Function;

    struct TruncInstOpts : InstOpts {
        // TODO
    };

    class TruncInst : public Inst {
    public:
        explicit TruncInst(TruncInstOpts opts);

        void accept(Pass &visitor) override;
    };
}
