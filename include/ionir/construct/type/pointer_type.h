#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    class PointerType : public Type, public Wrapper<ionshared::Ptr<Type>> {
    public:
        explicit PointerType(ionshared::Ptr<Type> type);

        void accept(Pass &pass) override;
    };
}
