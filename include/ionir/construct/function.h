#pragma once

#include <ionir/tracking/local_var_descriptor.h>
#include <ionir/tracking/symbol_table.h>
#include "construct.h"
#include "prototype.h"
#include "function_body.h"

namespace ionir {
    class Pass;

    class Function : public Construct {
    private:
        ionshared::Ptr<Prototype> prototype;

        ionshared::Ptr<FunctionBody> body;

        PtrSymbolTable<LocalVariableDescriptor> localVariables;

    public:
        Function(ionshared::Ptr<Prototype> prototype, ionshared::Ptr<FunctionBody> body);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Prototype> getPrototype() const noexcept;

        void setPrototype(ionshared::Ptr<Prototype> prototype);

        [[nodiscard]] ionshared::Ptr<FunctionBody> getBody() const noexcept;

        // TODO: Should this automatically set the body's parent as well?
        void setBody(const ionshared::Ptr<FunctionBody> &body) noexcept;

        [[nodiscard]] PtrSymbolTable<LocalVariableDescriptor> getLocalVariables() const;

        void setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables);

        bool verify() override;
    };
}
