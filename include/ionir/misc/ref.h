#pragma once

#include <optional>
#include <string>
#include <utility>
#include <ionshared/misc/named.h>
#include <ionshared/misc/util.h>
#include <ionir/construct/construct.h>
#include <ionir/construct/basic_block.h>
#include <ionir/misc/util.h>
#include <ionir/construct/inst/alloca.h>

namespace ionir {
    // TODO: This RefKind system may be flawed. What about refs for Globals?
    enum class RefKind {
        Module,

        Extern,

        Function,

        BasicBlock,

        Inst
    };

    template<typename T>
    class Ref : public ionshared::Named {
    private:
        RefKind kind;

        ionshared::Ptr<Construct> owner;

        ionshared::OptPtr<T> value;

    public:
        Ref(
            RefKind kind,
            const std::string &id,
            ionshared::Ptr<Construct> owner,
            ionshared::OptPtr<T> value = std::nullopt
        ) :
            Named(id),
            kind(kind),
            owner(std::move(owner)),
            value(value) {
            //
        }

        [[nodiscard]] RefKind getRefKind() const noexcept {
            return this->kind;
        }

        [[nodiscard]] ionshared::Ptr<Construct> getOwner() const noexcept {
            return this->owner;
        }

        void setOwner(const ionshared::Ptr<Construct> &owner) noexcept {
            this->owner = owner;
        }

        [[nodiscard]] ionshared::OptPtr<T> getValue() const noexcept {
            return this->value;
        }

        template<typename TValue>
        [[nodiscard]] ionshared::OptPtr<TValue> getValueAs() const {
            // TODO: Ensure T is or derives from Construct.

            ionshared::OptPtr<Construct> value = this->getValue();

            if (ionshared::util::hasValue(value)) {
                return value->get()->dynamicCast<TValue>();
            }

            return std::nullopt;
        }

        [[nodiscard]] bool isResolved() noexcept {
            return ionshared::util::hasValue(this->value);
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

    template<typename T>
    using PtrRef = ionshared::Ptr<Ref<T>>;

    template<typename T>
    using OptPtrRef = std::optional<PtrRef<T>>;
}
