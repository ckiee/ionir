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

    struct Prototype : public ChildConstruct<Module>, public ionshared::Named {
        std::string id;

        ionshared::Ptr<Args> args;

        ionshared::Ptr<Type> returnType;

        Prototype(
            std::string id,
            ionshared::Ptr<Args> args,
            ionshared::Ptr<Type> returnType,
            ionshared::Ptr<Module> parent
        );

        void accept(Pass &visitor) override;

        [[nodiscard]] Ast getChildrenNodes() override;

        [[nodiscard]] bool verify() override;
    };
}
