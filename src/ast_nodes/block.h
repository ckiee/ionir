#pragma once

#include <optional>
#include <vector>
#include "code_gen/node.h"
#include "section.h"

namespace ionir
{
class Pass;

class Block : public Node
{
protected:
    std::vector<Section *> sections;

    std::optional<Section *> cachedEntry;

public:
    Block(std::vector<Section *> sections = {});

    Node *accept(Pass *visitor) override;

    bool verify() const override;

    std::optional<Section *> getEntrySection();

    std::vector<Section *> getSections() const;
};
} // namespace ionir
