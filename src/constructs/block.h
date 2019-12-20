#pragma once

#include <memory>
#include <optional>
#include <vector>
#include "constructs/construct.h"
#include "misc/helpers.h"
#include "section.h"

namespace ionir
{
class Pass;

class Block : public Construct
{
protected:
    std::vector<Ptr<Section>> sections;

    std::optional<Ptr<Section>> cachedEntry;

public:
    Block(std::vector<Ptr<Section>> sections = {});

    void accept(Pass *visitor) override;

    bool verify() const override;

    std::optional<Ptr<Section>> getEntrySection();

    std::vector<Ptr<Section>> &getSections();

    void setSections(std::vector<Ptr<Section>> sections);
};
} // namespace ionir
