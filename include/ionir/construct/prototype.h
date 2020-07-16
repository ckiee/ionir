#pragma once

#include <string>
#include <vector>
#include <ionshared/misc/named.h>
#include <ionir/construct/pseudo/args.h>
#include <ionir/misc/helpers.h>
#include "child_construct.h"
#include "type.h"
#include "module.h"

namespace ionir {
    class Pass;

    class Prototype : public ChildConstruct<Module>, public ionshared::Named {
    private:
        std::string id;

        ionshared::Ptr<Args> args;

        ionshared::Ptr<Type> returnType;

    public:
        Prototype(std::string id, ionshared::Ptr<Args> args, ionshared::Ptr<Type> returnType, ionshared::Ptr<Module> parent);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        ionshared::Ptr<Args> getArgs() const noexcept;

        void setArgs(ionshared::Ptr<Args> args) noexcept;

        ionshared::Ptr<Type> getReturnType() const noexcept;

        void setReturnType(ionshared::Ptr<Type> returnType) noexcept;

        bool verify() override;
    };
}
