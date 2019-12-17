#pragma once

#include <memory>
#include "code_gen/node_kind.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Construct : public std::enable_shared_from_this<Construct>
{
protected:
    ConstructKind type;

public:
    Construct(ConstructKind type);

    virtual Ptr<Construct> accept(Pass *visitor) = 0;

    ConstructKind getConstructKind() const;

    /**
     * Verify the members and properties of the node.
     * Without an implementation by the derived class,
     * this will always return true.
     */
    virtual bool verify() const;

    Ptr<Construct> getPtr();

    template <class T>
    Ptr<T> cast()
    {
        return std::static_pointer_cast<T>(this->shared_from_this());
    }
};
} // namespace ionir
