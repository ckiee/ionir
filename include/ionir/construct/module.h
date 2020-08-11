#pragma once

#include <string>
#include <ionshared/misc/util.h>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/scope_anchor.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Function;

    class Module : public Construct, public ScopeAnchor<>, public ionshared::Named {
    public:
        explicit Module(std::string id, PtrSymbolTable<Construct> symbolTable = ionshared::Util::makePtrSymbolTable<Construct>());

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        void insertFunction(ionshared::Ptr<Function> function);

        ionshared::OptPtr<Function> lookupFunction(std::string id);
    };
}
