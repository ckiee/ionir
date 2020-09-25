#pragma once

#include <string>
#include <ionir/construct/type.h>
#include <ionir/construct/inst.h>

namespace ionir {
    class Pass;

    struct ReturnInstOpts : InstOpts {
        ionshared::OptPtr<Construct> value = std::nullopt;
    };

    class ReturnInst : public Inst {
    private:
        ionshared::OptPtr<Construct> value;

    public:
        explicit ReturnInst(const ReturnInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildrenNodes() override;

        [[nodiscard]] ionshared::OptPtr<Construct> getValue() const noexcept;

        void setValue(ionshared::OptPtr<Construct> value) noexcept;

        [[nodiscard]] bool hasValue() noexcept;

        void removeValue() noexcept;
    };
}
