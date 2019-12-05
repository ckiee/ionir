#pragma once

#include <vector>
#include <utility>
#include <string>
#include "type.h"

namespace ionir
{
typedef std::pair<Type *, std::string> Arg;

class Args
{
protected:
    std::vector<Arg> items;

    bool isInfinite;

public:
    Args(std::vector<Arg> items = {}, bool isInfinite = false);

    std::vector<Arg> getItems() const;

    bool getIsInfinite() const;
};
} // namespace ionir
