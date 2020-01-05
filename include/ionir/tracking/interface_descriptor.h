#pragma once

#include <optional>
#include <vector>
#include <string>
#include "field_descriptor.h"
#include "method_descriptor.h"
#include "symbol_table.h"

namespace ionir {
    class InterfaceDescriptor {
    private:
        std::string name;

        SymbolTable<FieldDescriptor> fields;

        SymbolTable<MethodDescriptor> methods;

        std::vector<Ptr<InterfaceDescriptor>> interfaces;

    public:
        std::string getName() const;

        void setName(std::string name);

        SymbolTable<FieldDescriptor> getFields() const;

        void setFields(SymbolTable<FieldDescriptor> fields);

        SymbolTable<MethodDescriptor> getMethods() const;

        void setMethods(SymbolTable<MethodDescriptor> methods);

        std::vector<Ptr<InterfaceDescriptor>> getInterfaces() const;

        void setInterfaces(std::vector<Ptr<InterfaceDescriptor>> interfaces);

        std::optional<Ptr<FieldDescriptor>> findField(std::string name) const;

        bool containsField(std::string name) const;
    };
}
