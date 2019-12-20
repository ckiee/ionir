#pragma once

#include "parsing/scope.h"
#include "inst_opts.h"

namespace ionir
{
struct PartialInstOpts : InstOpts
{
    Ptr<Scope> scope;
};
} // namespace ionir
