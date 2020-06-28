#pragma once

#include <string>
#include <vector>
#include <ionir/construct/pseudo/args.h>
#include <ionir/misc/helpers.h>
#include <ionir/misc/named.h>
#include "child_construct.h"
#include "type.h"
#include "module.h"

namespace ionir {
    class Pass;

    class Prototype : public ChildConstruct<Module>, public Named {
    private:
        std::string id;

        Ptr<Args> args;

        Ptr<Type> returnType;

    public:
        Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType, Ptr<Module> parent);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        Ptr<Args> getArgs() const noexcept;

        void setArgs(Ptr<Args> args) noexcept;

        Ptr<Type> getReturnType() const noexcept;

        void setReturnType(Ptr<Type> returnType) noexcept;

        bool verify() override;
    };
}
