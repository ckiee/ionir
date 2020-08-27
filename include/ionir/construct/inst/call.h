#pragma once

#include <string>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/construct/inst_yield.h>

namespace ionir {
    class Pass;

    class Function;

    struct CallInstOpts : InstOpts {
        OptPtrRef<Function> callee = std::nullopt;
    };

    class CallInst : public Inst {
    private:
        OptPtrRef<Function> callee;

    public:
        explicit CallInst(const CallInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] OptPtrRef<Function> getCallee() const;

        void setCallee(OptPtrRef<Function> callee);
    };
}
