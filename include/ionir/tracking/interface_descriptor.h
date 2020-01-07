#pragma once

#include <optional>
#include <vector>
#include <string>
#include "field_descriptor.h"
#include "symbol_table.h"

namespace ionir {
    class InterfaceDescriptor {
    private:
        std::string name;

        PtrSymbolTable<FieldDescriptor> fields;

        //        PtrSymbolTable<MethodDescriptor> methods;

        std::vector<Ptr<InterfaceDescriptor>> interfaces;

    public:
        std::string getName() const;

        void setName(std::string name);

        PtrSymbolTable<FieldDescriptor> getFields() const;

        void setFields(PtrSymbolTable<FieldDescriptor> fields);

        //PtrSymbolTable<MethodDescriptor> getMethods() const;

        //void setMethods(PtrSymbolTable<MethodDescriptor> methods);

        std::vector<Ptr<InterfaceDescriptor>> getInterfaces() const;

        void setInterfaces(std::vector<Ptr<InterfaceDescriptor>> interfaces);

        std::optional<Ptr<FieldDescriptor>> findField(std::string name);

        bool containsField(std::string name);
    };
}
