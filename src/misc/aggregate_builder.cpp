#include "aggregate_builder.h"

namespace ionir
{
AggregateBuilder::AggregateBuilder() : builder()
{
    //
}

std::vector<Node> AggregateBuilder::getParts() const
{
    return this->parts;
}

void AggregateBuilder::clear()
{
    this->parts.clear();
}
} // namespace ionir
