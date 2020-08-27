#pragma once

#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    class Function;

    struct IcmpInstOpts : InstOpts {
        // TODO
    };

    class IcmpInst : public Inst {
    public:
        explicit IcmpInst(const IcmpInstOpts &opts);

        void accept(Pass &visitor) override;
    };
}
