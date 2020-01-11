#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/tracking/local_var_descriptor.h>
#include <ionir/tracking/symbol_table.h>
#include "construct.h"
#include "prototype.h"
#include "block.h"

namespace ionir {
    class Pass;

    class Function : public Construct {
    private:
        Ptr<Prototype> prototype;

        Ptr<Block> body;

        PtrSymbolTable<LocalVariableDescriptor> localVariables;

    public:
        Function(Ptr<Prototype> prototype, Ptr<Block> body);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Prototype> getPrototype() const;

        void setPrototype(Ptr<Prototype> prototype);

        Ptr<Block> getBody() const;

        void setBody(Ptr<Block> body);

        PtrSymbolTable<LocalVariableDescriptor> getLocalVariables() const;

        void setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables);

        bool verify() const override;
    };
}
