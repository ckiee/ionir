#include "pass.h"

namespace ionir
{
Node *Pass::visit(Node *node)
{
    return node->accept(this);
}
} // namespace ionir
