#pragma once

#include <ionshared/misc/named.h>
#include "construct.h"

namespace ionir {
    class Pass;

    typedef ionshared::PtrSymbolTable<Type> Fields;

    class Struct : public Construct, public ionshared::Named {
    private:
        Fields fields;

    public:
        Struct(std::string name, Fields fields);

        void accept(Pass &visitor) override;

        [[nodiscard]] Ast getChildNodes() override;

        [[nodiscard]] Fields getFields() const noexcept;

        void setFields(Fields fields) noexcept;

        [[nodiscard]] bool containsField(std::string name) const;

        [[nodiscard]] ionshared::OptPtr<Type> lookupField(std::string name);

        void setField(std::string name, ionshared::Ptr<Type> field);
    };
}
