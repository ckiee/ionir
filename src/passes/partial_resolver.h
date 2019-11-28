#pragma once

#include <vector>
#include "parsing/partial_inst.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<PartialInst *> partials;

    void resolvePartial(PartialInst *partial);

public:
    PartialResolverPass(std::vector<PartialInst *> partials);

    std::vector<PartialInst *> getPartials() const;

    Node *visitInst(Inst *node) override;
};
} // namespace ionir
