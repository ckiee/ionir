#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    struct ArrayDescriptor {
        Ptr<Type> type;

        uint32_t size;
    };
}
