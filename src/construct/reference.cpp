#include "construct/construct_kind.h"
#include "passes/pass.h"
#include "reference.h"

namespace ionir
{
Reference::Reference(std::string id)
    : Construct(ConstructKind::Reference), id(id)
{
    //
}

void Reference::accept(Pass *visitor)
{
    visitor->visitReference(this->cast<Reference>());
}

std::string Reference::getId() const
{
    return this->id;
}

void Reference::setId(std::string id)
{
    this->id = id;
}
} // namespace ionir
