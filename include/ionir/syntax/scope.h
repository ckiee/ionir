#pragma once

#include <ionir/construct/construct.h>
#include <ionir/misc/wrapper.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    enum class ScopeKind {
        Block
    };

    class Scope : public Wrapper<ionshared::Ptr<Construct>> {
    private:
        ScopeKind kind;

    public:
        Scope(ionshared::Ptr<Construct> value, ScopeKind kind);

        ScopeKind getKind() const;
    };
}
