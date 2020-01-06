#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/construct/type/integer_type.h>
#include "ionir/construct/value.h"

namespace ionir {
    class Pass;

    class IntegerValue : public Value {
    private:
        Ptr<IntegerType> type;

        int64_t value;

    public:
        IntegerValue(Ptr<IntegerType> type, int64_t value);

        void accept(Pass &visitor) override;

        Ptr<IntegerType> getType() const;

        void setType(Ptr<IntegerType> type);

        int64_t getValue() const;

        void setValue(int64_t value);
    };
}
