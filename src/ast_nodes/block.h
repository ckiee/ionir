#pragma once

#include <memory>
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
    std::vector<std::shared_ptr<Section>> sections;

    std::optional<std::shared_ptr<Section>> cachedEntry;

public:
    Block(std::vector<std::shared_ptr<Section>> sections = {});

    ~Block();

    std::shared_ptr<Node> accept(Pass *visitor) override;

    bool verify() const override;

    std::optional<std::shared_ptr<Section>> getEntrySection();

    std::vector<std::shared_ptr<Section>> getSections() const;

    void setSections(std::vector<std::shared_ptr<Section>> sections);
};
} // namespace ionir
