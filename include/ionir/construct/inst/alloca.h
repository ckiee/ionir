#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst_yield.h>
#include <ionir/construct/inst.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class BasicBlock;

    struct AllocaInstOpts : InstOpts {
        ionshared::Ptr<Type> type;
    };

    class AllocaInst : public Inst {
    private:
        ionshared::Ptr<Type> type;

    public:
        // TODO: Missing support for array-type allocas.
        explicit AllocaInst(const AllocaInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] ionshared::Ptr<Type> getType() const;

        void setType(ionshared::Ptr<Type> type);
    };
}
