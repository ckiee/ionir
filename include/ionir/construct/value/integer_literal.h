#pragma once

#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    struct IntegerLiteral : Value<IntegerType> {
        int64_t value;

        IntegerLiteral(ionshared::Ptr<IntegerType> type, int64_t value);

        void accept(Pass &visitor) override;
    };
}
