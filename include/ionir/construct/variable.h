#pragma once

#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class Variable : public Construct {
    private:
        Ptr<Construct> value;

    public:
        explicit Variable(Ptr<Construct> value);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        Ptr<Construct> getValue() const noexcept;

        void setValue(Ptr<Construct> value) noexcept;
    };
}
