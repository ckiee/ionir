#pragma once

#include <ionir/misc/helpers.h>
#include "construct.h"
#include "prototype.h"

namespace ionir {
    class Pass;

    class Extern : public Construct {
    private:
        Ptr <Prototype> prototype;

    public:
        explicit Extern(Ptr <Prototype> prototype);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr <Prototype> getPrototype() const noexcept;

        void setPrototype(Ptr <Prototype> prototype) noexcept;
    };
}
