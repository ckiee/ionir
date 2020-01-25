#pragma once

#include <optional>
#include <string>
#include <ionir/misc/helpers.h>
#include "value.h"
#include "construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    class Global : public Construct, public Named {
    private:
        Ptr<Type> type;

        std::string id;

        OptPtr<Value<>> value;

    public:
        Global(Ptr<Type> type, std::string id, OptPtr<Value<>> value = std::nullopt);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        Ptr<Type> getType() const;

        void setType(Ptr<Type> type);

        OptPtr<Value<>> getValue() const;

        void setValue(OptPtr<Value<>> value);
    };
}
