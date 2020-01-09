#pragma once

#include <string>
#include <ionir/construct/construct.h>

namespace ionir {
    template<typename T = Construct>
    class Reference {
    private:
        std::string id;

        Ptr<Construct> owner;

        OPtr<T> value;

    public:
        Reference(std::string id, Ptr<Construct> owner, OPtr<T> value = std::nullopt);

        std::string getId() const;

        void setId(std::string id);

        Ptr<Construct> getOwner() const;

        void setOwner(Ptr<Construct> owner);

        OPtr<T> getValue() const;

        template<typename TValue>
        OPtr<TValue> getValueAs() const {
            // TODO: Ensure T is or derives from Construct.

            OPtr<Construct> value = this->getValue();

            if (value.has_value()) {
                return value->get()->cast<TValue>();
            }

            return std::nullopt;
        }

        bool isResolved() const;

        void resolve(OPtr<T> value);
    };

    template<typename T = Construct>
    using PtrReference = Reference<T>;
}
