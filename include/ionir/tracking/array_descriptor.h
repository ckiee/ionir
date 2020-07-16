#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    struct ArrayDescriptor {
        ionshared::Ptr<Type> type;

        uint32_t size;
    };
}
