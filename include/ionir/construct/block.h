#pragma once

#include <optional>
#include <vector>
#include <functional>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/scope_anchor.h>
#include "child_construct.h"
#include "section.h"

namespace ionir {
    class Pass;

    class Function;

    class Block : public ChildConstruct<Function>, ScopeAnchor<Section> {
    private:
        std::optional<Ptr<Section>> cachedEntry;

    public:
        explicit Block(Ptr<Function> parent, std::vector<Ptr<Section>> sections = {});

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        bool verify() const override;

        std::optional<Ptr<Section>> getEntrySection();
    };
}
