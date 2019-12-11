#pragma once

#include <memory>
#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class Pass;

class Type : public Node
{
protected:
    std::string id;

    bool isPointer;

public:
    Type(std::string id, bool isPointer = false);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);

    bool getIsPointer() const;

    void setIsPointer(bool isPointer);
};
} // namespace ionir
