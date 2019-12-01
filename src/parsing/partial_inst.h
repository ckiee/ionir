#pragma once

#include <exception>
#include <optional>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "scope.h"

namespace ionir
{
template <typename T>
class PartialInst : public Inst
{
private:
    std::optional<T> value;

    Scope *scope;

protected:
    std::optional<T> getValue() const
    {
        return this->value;
    }

public:
    PartialInst(InstKind kind, Scope *scope, std::optional<T *> value = std::nullopt)
        : Inst(kind), scope(scope), value(value)
    {
        //
    }

    virtual Node *accept(Pass *visitor) = 0;

    Scope *getScope() const
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
