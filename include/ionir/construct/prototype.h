#pragma once

#include <string>
#include <vector>
#include <ionir/construct/psuedo/args.h>
#include <ionir/misc/helpers.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Prototype : public Construct {
    protected:
        std::string id;

        Ptr<Args> args;

        Ptr<Type> returnType;

    public:
        Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType);

        void accept(Pass &visitor) override;

        ConstructChildren getChildren() const override;

        std::string getId() const;

        void setId(std::string id);

        Ptr<Args> getArgs() const;

        void setArgs(Ptr<Args> args);

        Ptr<Type> getReturnType() const;

        void setReturnType(Ptr<Type> returnType);

        bool verify() const override;
    };
}
