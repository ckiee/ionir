#pragma once

#include <vector>
#include <utility>
#include <string>
#include <ionir/construct/type.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    typedef std::pair<ionshared::Ptr<Type>, std::string> Arg;

    class Args {
    private:
        ionshared::Ptr<ionshared::SymbolTable<Arg>> items;

        bool isVariable;

    public:
        explicit Args(
            ionshared::Ptr<ionshared::SymbolTable<Arg>> items =
                std::make_shared<ionshared::SymbolTable<Arg>>(),

            bool isVariable = false
        );

        [[nodiscard]] ionshared::Ptr<ionshared::SymbolTable<Arg>> getItems() const noexcept;

        void setItems(ionshared::Ptr<ionshared::SymbolTable<Arg>> items) noexcept;

        [[nodiscard]] bool getIsVariable() const noexcept;

        void setIsVariable(bool isInfinite) noexcept;
    };
}
