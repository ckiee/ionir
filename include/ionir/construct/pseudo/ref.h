#pragma once

#include <optional>
#include <string>
#include <utility>
#include <ionshared/misc/named.h>
#include <ionshared/misc/util.h>
#include <ionir/construct/construct.h>
#include <ionir/misc/util.h>

namespace ionir {
    // TODO: What if 'pass.h' is never included?
    class Pass;

    template<typename T = Construct>
    class Ref : public Construct, public ionshared::Named {
    private:
        ionshared::Ptr<Construct> owner;

        ionshared::OptPtr<T> value;

    public:
        Ref(
            const std::string &id,
            ionshared::Ptr<Construct> owner,
            ionshared::OptPtr<T> value = std::nullopt
        ) :
            Construct(ConstructKind::Ref),
            Named(id), owner(std::move(owner)),
            value(value) {
            //
        }

        void accept(Pass &visitor) override {
            // TODO: CRITICAL: Fix 'incomplete type' problem.
            // visitor.visitRef(this->dynamicCast<Ref<T>>());
        }

        ionshared::Ptr<Construct> getOwner() const noexcept {
            return this->owner;
        }

        void setOwner(const ionshared::Ptr<Construct> &owner) noexcept {
            this->owner = owner;
        }

        ionshared::OptPtr<T> getValue() const noexcept {
            return this->value;
        }

        template<typename TValue>
        ionshared::OptPtr<TValue> getValueAs() const {
            // TODO: Ensure T is or derives from Construct.

            ionshared::OptPtr<Construct> value = this->getValue();

            if (ionshared::Util::hasValue(value)) {
                return value->get()->dynamicCast<TValue>();
            }

            return std::nullopt;
        }

        bool isResolved() noexcept {
            return ionshared::Util::hasValue(this->value);
        }

        void resolve(ionshared::OptPtr<T> value) {
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
    using PtrRef = ionshared::Ptr<Ref<T>>;

    template<typename T = Construct>
    using OptPtrRef = std::optional<PtrRef<T>>;
}
