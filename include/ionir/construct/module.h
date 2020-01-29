#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/scope_anchor.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Module : public Construct, public ScopeAnchor<>, public Named {
    public:
        explicit Module(std::string id, PtrSymbolTable<Construct> symbolTable = TypeFactory::makePtrSymbolTable<>());

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        void insertFunction(Ptr<Function> function);

        OptPtr<Function> lookupFunction(std::string id);
    };
}
