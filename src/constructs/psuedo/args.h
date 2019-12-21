#pragma once

#include <vector>
#include <utility>
#include <string>
#include "misc/helpers.h"
#include "constructs/type.h"

namespace ionir
{
typedef std::pair<Ptr<Type>, std::string> Arg;

class Args
{
protected:
    std::vector<Arg> items;

    bool isInfinite;

public:
    Args(std::vector<Arg> items = {}, bool isInfinite = false);

    std::vector<Arg> getItems() const;

    bool getIsInfinite() const;

    void setIsInfinite(bool isInfinite);
};
} // namespace ionir
