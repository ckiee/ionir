#pragma once

#include <optional>
#include <string>
#include "value.h"
#include "construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    struct Global : public Construct, public ionshared::Named {
        ionshared::Ptr<Type> type;

        ionshared::OptPtr<Value<>> value;

        Global(
            ionshared::Ptr<Type> type,
            std::string id,
            ionshared::OptPtr<Value<>> value = std::nullopt
        );

        void accept(Pass &visitor) override;

        [[nodiscard]] Ast getChildrenNodes() override;
    };
}
