#pragma once

#include <optional>
#include <vector>
#include <functional>
#include <ionir/misc/helpers.h>
#include <ionir/misc/static_factory.h>
#include <ionir/tracking/scope_anchor.h>
#include "child_construct.h"
#include "section.h"

namespace ionir {
    class Pass;

    class Function;

    class Block : public ChildConstruct<Function>, public ScopeAnchor<Section> {
    public:
        explicit Block(Ptr<Function> parent, PtrSymbolTable<Section> symbolTable = StaticFactory::makePtrSymbolTable<Section>());

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        bool verify() override;

        OptPtr<Section> getEntrySection();

        bool hasEntrySection();

        void insertSection(Ptr<Section> section);
    };
}
