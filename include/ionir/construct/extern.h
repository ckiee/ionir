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

        void accept(Pass *visitor) override;

        ConstructChildren getChildren() const override;

        Ptr <Prototype> getPrototype() const;

        void setPrototype(Ptr <Prototype> prototype);
    };
}
