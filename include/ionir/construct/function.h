#pragma once

#include <ionir/tracking/local_var_descriptor.h>
#include <ionir/tracking/symbol_table.h>
#include "construct.h"
#include "prototype.h"
#include "function_body.h"

namespace ionir {
    class Pass;

    struct Function : public Construct {
        ionshared::Ptr<Prototype> prototype;

        ionshared::Ptr<FunctionBody> body;

        PtrSymbolTable<LocalVariableDescriptor> localVariables;

        Function(
            ionshared::Ptr<Prototype> prototype,
            ionshared::Ptr<FunctionBody> body
        );

        void accept(Pass &visitor) override;

        Ast getChildrenNodes() override;

        bool verify() override;
    };
}
