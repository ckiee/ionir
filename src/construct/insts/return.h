#pragma once

#include <optional>
#include <string>
#include "construct/insts/inst.h"
#include "construct/type.h"
#include "construct/values/value.h"
#include "misc/helpers.h"

namespace ionir {
    class Pass;

    struct ReturnInstOpts : InstOpts {
        std::optional<Ptr < Value>> value = std::nullopt;
    };

    class ReturnInst : public Inst {
    protected:
        std::optional<Ptr < Value>> value;

    public:
        ReturnInst(ReturnInstOpts opts);

        void accept(Pass *visitor) override;

        std::optional<Ptr < Value>> getValue() const;

        void setValue(std::optional<Ptr < Value>>

        value);
    };
}
