#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    struct ReturnInstOpts : InstOpts {
        ionshared::OptPtr<Construct> value = std::nullopt;
    };

    struct ReturnInst : Inst {
        ionshared::OptPtr<Construct> value;

        explicit ReturnInst(const ReturnInstOpts &opts);

        void accept(Pass &visitor) override;

        [[nodiscard]] Ast getChildrenNodes() override;

        [[nodiscard]] bool hasValue() noexcept;

        void removeValue() noexcept;
    };
}
