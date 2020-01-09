#pragma once

#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/partial_inst.h>
#include <ionir/construct/child_construct.h>

namespace ionir {
    class Pass;

    struct StoreInstPartials {
        // TODO
    };

    struct StoreInstOpts : InstOpts {
        // TODO
    };

    class StoreInst : public PartialInst<StoreInstPartials> {
    public:
        explicit StoreInst(StoreInstOpts opts);

        void accept(Pass &visitor) override;
    };
}
