#pragma once

#include <memory>
#include <string>
#include "ast_nodes/inst.h"
#include "ast_nodes/inst_kind.h"
#include "ast_nodes/type.h"

namespace ionir
{
class AllocaInst : public Inst
{
protected:
    std::string id;

    std::shared_ptr<Type> type;

public:
    // TODO: Missing support for array type allocas.
    AllocaInst(std::string id, std::shared_ptr<Type> type);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);

    std::shared_ptr<Type> getType() const;

    void setType(std::shared_ptr<Type> type);
};
} // namespace ionir
