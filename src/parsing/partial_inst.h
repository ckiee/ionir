#pragma once

#include <optional>
#include "ast_nodes/inst.h"
#include "scope.h"

namespace ionir
{
class PartialInst
{
protected:
    std::optional<Inst *> inst;

    Scope *scope;

public:
    PartialInst(Scope *scope, std::optional<Inst *> inst = std::nullopt);

    Scope *getScope() const;

    std::optional<Inst *> getInst() const;

    bool isResolved() const;

    void resolve(Inst *inst);
};
} // namespace ionir
