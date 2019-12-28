#pragma once

#include <optional>
#include <string>
#include <ionir/syntax/scope.h>
#include <ionir/construct/function.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    struct CallInstOpts : InstOpts {
        std::string target;

        std::optional<Ptr<Function>> callee = std::nullopt;
    };

    class CallInst : public Inst {
    protected:
        std::string target;

    public:
        CallInst(CallInstOpts opts);

        void accept(Pass *visitor) override;

        std::string getTarget() const;

        void setTarget(std::string target);
    };
}
