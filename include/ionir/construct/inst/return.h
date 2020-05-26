#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    struct ReturnInstOpts : InstOpts {
        OptPtr<Construct> value = std::nullopt;
    };

    class ReturnInst : public Inst {
    private:
        OptPtr<Construct> value;

    public:
        explicit ReturnInst(ReturnInstOpts opts);

        void accept(Pass &visitor) override;

        OptPtr<Construct> getValue() const noexcept;

        void setValue(OptPtr<Construct> value) noexcept;
    };
}
