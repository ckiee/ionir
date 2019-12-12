#pragma once

#include <memory>
#include <vector>
#include "code_gen/node.h"

namespace ionir
{
typedef std::vector<std::shared_ptr<Node>> Ast;
} // namespace ionir
