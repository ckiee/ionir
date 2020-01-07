#pragma once

#include <optional>
#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/value.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    struct ReturnInstOpts : InstOpts {
        std::optional<Ptr < Value>> value = std::nullopt;
    };

    class ReturnInst : public Inst {
    private:
        std::optional<Ptr < Value>> value;

    public:
        explicit ReturnInst(ReturnInstOpts opts);

        void accept(Pass &visitor) override;

        std::optional<Ptr < Value>> getValue() const;

        void setValue(std::optional<Ptr < Value>>

        value);
    };
}
