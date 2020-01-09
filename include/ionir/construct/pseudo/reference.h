#pragma once

#include <string>
#include <ionir/construct/construct.h>

namespace ionir {
    class Reference {
    private:
        std::string id;

        Ptr<Construct> owner;

        OPtr<Construct> value;

    public:
        Reference(std::string id, Ptr<Construct> owner, OPtr<Construct> value = std::nullopt);

        std::string getId() const;

        void setId(std::string id);

        Ptr<Construct> getOwner() const;

        void setOwner(Ptr<Construct> owner);

        OPtr<Construct> getValue() const;

        bool isResolved() const;

        void resolve(OPtr<Construct> value);
    };
}
