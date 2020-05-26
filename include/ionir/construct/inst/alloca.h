#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst_yield.h>
#include <ionir/construct/inst.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class BasicBlock;

    struct AllocaInstOpts : InstOpts {
        std::string yieldId;

        Ptr<Type> type;
    };

    class AllocaInst : public Inst, public InstYield {
    private:
        Ptr<Type> type;

    public:
        // TODO: Missing support for array-type allocas.
        explicit AllocaInst(AllocaInstOpts opts);

        void accept(Pass &visitor) override;

        Ptr<Type> getType() const;

        void setType(Ptr<Type> type);
    };
}
