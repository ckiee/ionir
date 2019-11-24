#pragma once

#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

class Type : public Node
{
protected:
    std::string identifier;

    bool isPointer;

public:
    Type(std::string identifier, bool isPointer);

    Node *accept(LlvmVisitor *visitor) override;

    std::string getIdentifier() const;

    bool getIsPointer() const;
};
} // namespace ionir
