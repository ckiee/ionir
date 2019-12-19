#include "constructs/construct_kind.h"
#include "passes/pass.h"
#include "reference.h"

namespace ionir
{
Reference::Reference(std::string id)
    : Construct(ConstructKind::Reference), id(id)
{
    //
}

Ptr<Construct> Reference::accept(Pass *visitor)
{
    return visitor->visitReference(this->cast<Reference>());
}

std::string Reference::getId() const
{
    return this->id;
}
} // namespace ionir
