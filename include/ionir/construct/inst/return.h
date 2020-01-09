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
        OPtr<Value> value = std::nullopt;
    };

    class ReturnInst : public Inst {
    private:
        OPtr<Value> value;

    public:
        explicit ReturnInst(ReturnInstOpts opts);

        void accept(Pass &visitor) override;

        OPtr<Value> getValue() const;

        void setValue(OPtr<Value> value);
    };
}
