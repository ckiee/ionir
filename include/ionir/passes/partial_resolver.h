#pragma once

#include <vector>
#include <ionir/construct/inst/inst.h>
#include <ionir/misc/helpers.h>
#include "pass.h"

namespace ionir {
    class PartialResolverPass : public Pass {
    protected:
        std::vector<Ptr<Inst>> partials;

    public:
        PartialResolverPass(std::vector<Ptr<Inst>> partials);

        std::vector<Ptr<Inst>> getPartials() const;
    };
}
