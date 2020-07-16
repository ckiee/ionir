#pragma once

#include <optional>
#include <string>
#include <ionir/misc/helpers.h>
#include "value.h"
#include "construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    class Global : public Construct, public ionshared::Named {
    private:
        Ptr<Type> type;

        std::string id;

        OptPtr<Value<>> value;

    public:
        Global(Ptr<Type> type, std::string id, OptPtr<Value<>> value = std::nullopt);

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        Ptr<Type> getType() const noexcept;

        void setType(Ptr<Type> type) noexcept;

        OptPtr<Value<>> getValue() const noexcept;

        void setValue(OptPtr<Value<>> value) noexcept;
    };
}
