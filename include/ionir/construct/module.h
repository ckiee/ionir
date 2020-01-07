#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/symbol_table.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Module : public Construct {
    private:
        std::string id;

        PtrSymbolTable <Construct> constructs;

    public:
        explicit Module(std::string id, PtrSymbolTable <Construct> constructs = {});

        void accept(Pass &visitor) override;

        ConstructChildren getChildren() const override;

        std::string getId() const;

        void setId(std::string id);

        PtrSymbolTable <Construct> getConstructs() const;

        void setConstructs(PtrSymbolTable <Construct> constructs);
    };
}
