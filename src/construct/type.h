#pragma once

#include <string>
#include "construct/construct.h"
#include "construct/construct_kind.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Type : public Construct
{
protected:
    std::string id;

    bool isPointer;

public:
    explicit Type(std::string id, bool isPointer = false);

    void accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);

    bool getIsPointer() const;

    void setIsPointer(bool isPointer);
};
} // namespace ionir
