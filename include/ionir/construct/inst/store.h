#pragma once

#include <ionir/construct/value/value.h>
#include <ionir/construct/psuedo/partial_inst.h>
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
