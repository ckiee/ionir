#pragma once

#include <optional>
#include <string>
#include <ionir/construct/construct.h>
#include <ionir/misc/named.h>

namespace ionir {
    // TODO: What if 'pass.h' is never included?
    class Pass;

    template<typename T = Construct>
    class Ref : public Construct, public Named {
    private:
        Ptr<Construct> owner;

        OptPtr<T> value;

    public:
        Ref(std::string id, Ptr<Construct> owner, OptPtr<T> value = std::nullopt)
            : Construct(ConstructKind::Ref), Named(id), owner(owner), value(value) {
            //
        }

        void accept(Pass &visitor) override {
            // TODO: CRITICAL: Fix 'incomplete type' problem.
            // visitor.visitRef(this->cast<Ref<T>>());
        }

        Ptr<Construct> getOwner() const {
            return this->owner;
        }

        void setOwner(Ptr<Construct> owner) {
            this->owner = owner;
        }

        OptPtr<T> getValue() const {
            return this->value;
        }

        template<typename TValue>
        OptPtr<TValue> getValueAs() const {
            // TODO: Ensure T is or derives from Construct.

            OptPtr<Construct> value = this->getValue();

            if (value.has_value()) {
                return value->get()->cast<TValue>();
            }

            return std::nullopt;
        }

        bool isResolved() const {
            return this->getValue() != std::nullopt;
        }

        void resolve(OptPtr<T> value) {
            this->value = value;
        }
    };

    template<typename T = Construct>
    using PtrRef = Ptr<Ref<T>>;

    template<typename T = Construct>
    using OptPtrRef = std::optional<PtrRef<T>>;
}
