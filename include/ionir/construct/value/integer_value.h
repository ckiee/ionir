#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    class IntegerValue : public Value<IntegerType> {
    private:
        int64_t value;

    public:
        IntegerValue(ionshared::Ptr<IntegerType> type, int64_t value);

        void accept(Pass &visitor) override;

        int64_t getValue() const;

        void setValue(int64_t value);
    };
}
