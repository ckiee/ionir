#pragma once

#include <string>
#include <vector>
#include <ionir/construct/pseudo/args.h>
#include <ionir/misc/helpers.h>
#include <ionir/misc/named.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Prototype : public Construct, public Named {
    private:
        std::string id;

        Ptr<Args> args;

        Ptr<Type> returnType;

    public:
        Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Args> getArgs() const noexcept;

        void setArgs(Ptr<Args> args) noexcept;

        Ptr<Type> getReturnType() const noexcept;

        void setReturnType(Ptr<Type> returnType) noexcept;

        bool verify() override;
    };
}
