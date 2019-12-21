#pragma once

#include <string>
#include "construct/construct.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Reference : public Construct
{
protected:
    std::string id;

public:
    Reference(std::string id);

    void accept(Pass *visitor) override;

    std::string getId() const;

    void setId(std::string id);
};
} // namespace ionir
