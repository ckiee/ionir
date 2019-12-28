#pragma once

#include <ionir/construct/construct.h>
#include <ionir/misc/wrapper.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    enum class ScopeKind {
        Block
    };

    class Scope : public Wrapper<Ptr < Construct>>

{
    protected:

    ScopeKind kind;

    public:

    Scope(Ptr<Construct>

    value,

    ScopeKind kind

    );

    ScopeKind getKind() const;
};
}
