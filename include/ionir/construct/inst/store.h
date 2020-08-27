#pragma once

#include <ionir/construct/inst.h>
#include <ionir/construct/value.h>
#include <ionir/construct/pseudo/child_construct.h>
#include <ionir/construct/pseudo/ref.h>

namespace ionir {
    class Pass;

    struct StoreInstOpts : InstOpts {
        ionshared::Ptr<Value<>> value;

        PtrRef<AllocaInst> target;
    };

    class StoreInst : public Inst {
    private:
        ionshared::Ptr<Value<>> value;

        PtrRef<AllocaInst> target;

    public:
        explicit StoreInst(const StoreInstOpts &opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Value<>> getValue() const;

        void setValue(ionshared::Ptr<Value<>> value);

        [[nodiscard]] PtrRef<AllocaInst> getTarget() const;

        void setTarget(PtrRef<AllocaInst> target);
    };
}
