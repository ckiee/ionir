#pragma once

#include <string>
#include <vector>
#include <ionshared/misc/named.h>
#include <ionir/construct/pseudo/args.h>
#include "ionir/construct/pseudo/child_construct.h"
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
        Prototype(
            std::string id,
            ionshared::Ptr<Args> args,
            ionshared::Ptr<Type> returnType,
            ionshared::Ptr<Module> parent
        );

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Args> getArgs() const noexcept;

        void setArgs(ionshared::Ptr<Args> args) noexcept;

        [[nodiscard]] ionshared::Ptr<Type> getReturnType() const noexcept;

        void setReturnType(ionshared::Ptr<Type> returnType) noexcept;

        bool verify() override;
    };
}
