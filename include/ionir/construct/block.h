#pragma once

#include <optional>
#include <vector>
#include <ionir/misc/helpers.h>
#include "child_construct.h"
#include "section.h"

namespace ionir {
    class Pass;

    class Function;

    class Block : public ChildConstruct<Function> {
    private:
        std::vector<Ptr<Section>> sections;

        std::optional<Ptr<Section>> cachedEntry;

    public:
        explicit Block(Ptr<Function> parent, std::vector<Ptr<Section>> sections = {});

        void accept(Pass *visitor) override;

        ConstructChildren getChildren() const override;

        bool verify() const override;

        std::optional<Ptr<Section>> getEntrySection();

        std::vector<Ptr<Section>> &getSections();

        void setSections(std::vector<Ptr<Section>> sections);
    };
}
