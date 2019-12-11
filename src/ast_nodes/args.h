#pragma once

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include "type.h"

namespace ionir
{
typedef std::pair<std::shared_ptr<Type>, std::string> Arg;

class Args
{
protected:
    std::vector<Arg> items;

    bool isInfinite;

public:
    Args(std::vector<Arg> items = {}, bool isInfinite = false);

    std::vector<Arg> getItems() const;

    void setItems(std::vector<Arg> items);

    bool getIsInfinite() const;

    void setIsInfinite(bool isInfinite);
};
} // namespace ionir
