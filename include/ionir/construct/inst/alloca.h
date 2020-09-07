#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst_yield.h>
#include <ionir/construct/inst.h>

namespace ionir {
    class BasicBlock;

    struct AllocaInstOpts : InstYieldOpts {
        ionshared::Ptr<Type> type;
    };

    class AllocaInst : public Inst, public InstYield {
    private:
        ionshared::Ptr<Type> type;

    public:
        // TODO: Missing support for array-type allocas.
        explicit AllocaInst(const AllocaInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] ionshared::Ptr<Type> getType() const noexcept;

        void setType(ionshared::Ptr<Type> type) noexcept;
    };
}
