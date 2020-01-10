#pragma once

#include <optional>
#include <string>
#include <ionir/syntax/scope.h>
#include <ionir/construct/function.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    struct CallInstOpts : InstOpts {
        OptPtrRef<Function> callee = std::nullopt;
    };

    class CallInst : public Inst {
    private:
        OptPtrRef<Function> callee;

    public:
        explicit CallInst(CallInstOpts opts);

        void accept(Pass &visitor) override;

        OptPtrRef<Function> getCallee() const;

        void setCallee(OptPtrRef<Function> callee);
    };
}
