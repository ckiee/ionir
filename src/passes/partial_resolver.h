#pragma once

#include <memory>
#include <vector>
#include "constructs/insts/goto.h"
#include "constructs/inst.h"
#include "misc/helpers.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<Ptr<Inst>> partials;

    void resolveGotoInst(Ptr<GotoInst> partial);

public:
    PartialResolverPass(std::vector<Ptr<Inst>> partials);

    std::vector<Ptr<Inst>> getPartials() const;

    Ptr<Construct> visitGotoInst(Ptr<GotoInst> node);
};
} // namespace ionir
