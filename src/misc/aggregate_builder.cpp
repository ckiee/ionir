#include "aggregate_builder.h"

namespace ionir
{
AggregateBuilder::AggregateBuilder() : builder()
{
    //
}

std::vector<Construct> AggregateBuilder::getParts() const
{
    return this->parts;
}

void AggregateBuilder::clear()
{
    this->parts.clear();
}
} // namespace ionir
