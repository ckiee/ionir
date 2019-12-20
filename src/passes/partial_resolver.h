#pragma once

#include <memory>
#include <vector>
#include "constructs/insts/inst.h"
#include "misc/helpers.h"
#include "pass.h"

namespace ionir
{
class PartialResolverPass : public Pass
{
protected:
    std::vector<Ptr<Inst>> partials;

public:
    PartialResolverPass(std::vector<Ptr<Inst>> partials);

    std::vector<Ptr<Inst>> getPartials() const;
};
} // namespace ionir
