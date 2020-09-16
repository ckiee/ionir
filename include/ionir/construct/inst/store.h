#pragma once

#include <ionir/construct/inst.h>
#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/child_construct.h>

namespace ionir {
    class Pass;

    struct StoreInstOpts : InstOpts {
        ionshared::Ptr<Value<>> value;

        ionshared::Ptr<AllocaInst> target;
    };

    class StoreInst : public Inst {
    private:
        ionshared::Ptr<Value<>> value;

        ionshared::Ptr<AllocaInst> target;

    public:
        explicit StoreInst(const StoreInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Value<>> getValue() const;

        void setValue(ionshared::Ptr<Value<>> value);

        [[nodiscard]] ionshared::Ptr<AllocaInst> getTarget() const;

        void setTarget(ionshared::Ptr<AllocaInst> target);
    };
}
