#pragma once

#include <vector>
#include <ionir/construct/inst.h>
#include <ionir/misc/helpers.h>
#include "pass.h"

namespace ionir {
    class PartialResolverPass : public Pass {
    protected:
        std::vector<ionshared::Ptr<Inst>> partials;

    public:
        explicit PartialResolverPass(std::vector<ionshared::Ptr<Inst>> partials);

        std::vector<ionshared::Ptr<Inst>> getPartials() const;
    };
}
