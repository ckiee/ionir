#pragma once

#include <exception>
#include <optional>
#include <ionir/construct/inst/inst.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    template<typename T>
    struct PartialInstOpts : InstOpts {
        std::optional<T> value = std::nullopt;

        InstKind kind;
    };

    template<typename T>
    class PartialInst : public Inst {
    private:
        std::optional<T> value;

    protected:
        std::optional<const T> getValue() const {
            return this->value;
        }

    public:
        PartialInst(PartialInstOpts<T> opts)
            : Inst(opts.parent, opts.kind), value(opts.value) {
            //
        }

        virtual void accept(Pass &visitor) = 0;

        bool isResolved() const {
            return this->value.has_value();
        }

        void resolve(T value) {
            if (this->isResolved()) {
                throw std::runtime_error("Partial instruction has already been resolved");
            }

            this->value = value;
        }
    };
}
