#pragma once

#include <string>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/construct/inst_yield.h>

namespace ionir {
    class Pass;

    class Function;

    struct CallInstOpts : InstOpts {
        std::optional<std::string> yieldId;

        OptPtrRef<Function> callee = std::nullopt;
    };

    class CallInst : public Inst, public InstYield {
    private:
        OptPtrRef<Function> callee;

    public:
        explicit CallInst(CallInstOpts opts);

        void accept(Pass &visitor) override;

        OptPtrRef<Function> getCallee() const;

        void setCallee(OptPtrRef<Function> callee);
    };
}
