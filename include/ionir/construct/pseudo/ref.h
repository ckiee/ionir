#pragma once

#include <optional>
#include <string>
#include <ionshared/misc/named.h>
#include <ionir/construct/construct.h>
#include <ionir/misc/util.h>

namespace ionir {
    // TODO: What if 'pass.h' is never included?
    class Pass;

    template<typename T = Construct>
    class Ref : public Construct, public ionshared::Named {
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
            // visitor.visitRef(this->dynamicCast<Ref<T>>());
        }

        Ptr<Construct> getOwner() const noexcept {
            return this->owner;
        }

        void setOwner(Ptr<Construct> owner) noexcept {
            this->owner = owner;
        }

        OptPtr<T> getValue() const noexcept {
            return this->value;
        }

        template<typename TValue>
        OptPtr<TValue> getValueAs() const {
            // TODO: Ensure T is or derives from Construct.

            OptPtr<Construct> value = this->getValue();

            if (Util::hasValue(value)) {
                return value->get()->dynamicCast<TValue>();
            }

            return std::nullopt;
        }

        bool isResolved() noexcept {
            return Util::hasValue(this->value);
        }

        void resolve(OptPtr<T> value) {
            /**
             * Make sure the value is not a nullptr. To un-resolve the reference,
             * std::nullopt should be used instead.
             */
            if (value.has_value() && *value == nullptr) {
                throw std::runtime_error("Cannot resolve reference with a nullptr");
            }

            this->value = value;
        }
    };

    template<typename T = Construct>
    using PtrRef = Ptr<Ref<T>>;

    template<typename T = Construct>
    using OptPtrRef = std::optional<PtrRef<T>>;
}
