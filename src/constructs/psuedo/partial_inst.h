#pragma once

#include <exception>
#include <optional>
#include "constructs/insts/inst.h"
#include "constructs/insts/inst_kind.h"
#include "misc/helpers.h"
#include "parsing/scope.h"

namespace ionir
{
template <typename T>
struct PartialInstOpts : InstOpts
{
    InstKind kind;

    Ptr<Scope> scope;

    std::optional<T> value = std::nullopt;
};

template <typename T>
class PartialInst : public Inst
{
private:
    std::optional<T> value;

    Ptr<Scope> scope;

protected:
    std::optional<T> getValue() const
    {
        return this->value;
    }

public:
    PartialInst(PartialInstOpts opts)
        : Inst(opts.kind), scope(opts.scope), value(opts.value)
    {
        //
    }

    virtual void accept(Pass *visitor) = 0;

    Ptr<Scope> getScope() const
    {
        return this->scope;
    }

    bool isResolved() const
    {
        return this->value.has_value();
    }

    void resolve(T value)
    {
        if (this->isResolved())
        {
            throw std::runtime_error("Partial instruction has already been resolved");
        }

        this->value = value;
    }
};
} // namespace ionir
