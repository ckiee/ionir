#pragma once

#include <string>
#include "constructs/construct.h"
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

    Ptr<Construct> accept(Pass *visitor) override;

    std::string getId() const;
};
} // namespace ionir
