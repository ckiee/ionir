#pragma once

#include <optional>
#include <string>
#include "syntax/scope.h"
#include "construct/function.h"
#include "misc/helpers.h"

namespace ionir {
    class Pass;

    struct CallInstOpts : InstOpts {
        std::string target;

        std::optional<Ptr < Function>> callee = std::nullopt;
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
