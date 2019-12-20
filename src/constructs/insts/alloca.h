#pragma once

#include <memory>
#include <string>
#include "constructs/type.h"
#include "constructs/section.h"
#include "misc/helpers.h"
#include "inst.h"

namespace ionir
{
struct AllocaInstOpts : InstOpts
{
    std::string id;

    Ptr<Type> type;
};

class AllocaInst : public Inst
{
protected:
    std::string id;

    Ptr<Type> type;

public:
    // TODO: Missing support for array type allocas.
    AllocaInst(AllocaInstOpts opts);

    void accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);

    Ptr<Type> getType() const;

    void setType(Ptr<Type> type);
};
} // namespace ionir
