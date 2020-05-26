#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/tracking/local_var_descriptor.h>
#include <ionir/tracking/symbol_table.h>
#include "construct.h"
#include "prototype.h"
#include "function_body.h"

namespace ionir {
    class Pass;

    class Function : public Construct {
    private:
        Ptr<Prototype> prototype;

        Ptr<FunctionBody> body;

        PtrSymbolTable<LocalVariableDescriptor> localVariables;

    public:
        Function(Ptr<Prototype> prototype, Ptr<FunctionBody> body);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Prototype> getPrototype() const noexcept;

        void setPrototype(Ptr<Prototype> prototype);

        Ptr<FunctionBody> getBody() const noexcept;

        void setBody(Ptr<FunctionBody> body) noexcept;

        PtrSymbolTable<LocalVariableDescriptor> getLocalVariables() const;

        void setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables);

        bool verify() override;
    };
}
