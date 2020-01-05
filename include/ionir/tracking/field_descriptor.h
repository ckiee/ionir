#pragma once

#include "visibility_modifier.h"
#include "local_var_descriptor.h"

namespace ionir {
    struct FieldDescriptor : LocalVariableDescriptor {
        VisibilityModifier visibility;
    };
}
