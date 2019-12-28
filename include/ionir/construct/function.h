#pragma once

#include <ionir/misc/helpers.h>
#include "construct.h"
#include "prototype.h"
#include "block.h"

namespace ionir {
    class Pass;

    class Function : public Construct {
    protected:
        Ptr<Prototype> prototype;

        Ptr<Block> body;

    public:
        Function(Ptr<Prototype> prototype, Ptr<Block> body);

        void accept(Pass *visitor) override;

        Ptr<Prototype> getPrototype() const;

        void setPrototype(Ptr<Prototype> prototype);

        Ptr<Block> getBody() const;

        void setBody(Ptr<Block> body);

        bool verify() const override;
    };
}
