#pragma once

#include <string>
#include "symbol_table.h"
#include "local_var_descriptor.h"

namespace ionir {
    struct MethodDescriptor {
        std::string name;

        SymbolTable<LocalVariableDescriptor> localVariables;
    };
}
