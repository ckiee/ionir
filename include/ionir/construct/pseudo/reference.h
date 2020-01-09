#pragma once

#include <string>
#include <ionir/construct/construct.h>

namespace ionir {
    class Reference {
    private:
        std::string id;

        Ptr<Construct> owner;

    public:
        Reference(std::string id, Ptr<Construct> owner);

        std::string getId() const;

        void setId(std::string id);

        Ptr<Construct> getOwner() const;

        void setOwner(Ptr<Construct> owner);
    };
}
