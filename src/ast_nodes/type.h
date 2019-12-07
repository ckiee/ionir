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
    std::string id;

    bool isPointer;

public:
    Type(std::string id, bool isPointer = false);

    ~Type();

    Node *accept(Pass *visitor) override;

    std::string getId() const;

    bool getIsPointer() const;
};
} // namespace ionir
