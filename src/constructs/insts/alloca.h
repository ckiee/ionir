#pragma once

#include <memory>
#include <string>
#include "constructs/inst.h"
#include "constructs/inst_kind.h"
#include "constructs/type.h"
#include "misc/helpers.h"

namespace ionir
{
class AllocaInst : public Inst
{
protected:
    std::string id;

    Ptr<Type> type;

public:
    // TODO: Missing support for array type allocas.
    AllocaInst(std::string id, Ptr<Type> type);

    Ptr<Construct> accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);

    Ptr<Type> getType() const;

    void setType(Ptr<Type> type);
};
} // namespace ionir
