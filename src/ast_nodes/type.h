#pragma once

#include <string>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class Pass;

class Type : public Node
{
protected:
    std::string identifier;

    bool isPointer;

public:
    Type(std::string identifier, bool isPointer = false);

    Node *accept(Pass *visitor) override;

    std::string getIdentifier() const;

    bool getIsPointer() const;
};
} // namespace ionir
