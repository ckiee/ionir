#pragma once

#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    class Function;

    struct ZextInstOpts : InstOpts {
        // TODO
    };

    class ZextInst : public Inst {
    public:
        explicit ZextInst(ZextInstOpts opts);

        void accept(Pass &visitor) override;
    };
}
