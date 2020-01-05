#include <ionir/tracking/interface_descriptor.h>

namespace ionir {
    std::string InterfaceDescriptor::getName() const {
        return this->name;
    }

    void InterfaceDescriptor::setName(std::string name) {
        this->name = name;
    }

    SymbolTable<FieldDescriptor> InterfaceDescriptor::getFields() const {
        return this->fields;
    }

    void InterfaceDescriptor::setFields(SymbolTable<FieldDescriptor> fields) {
        this->fields = fields;
    }

    SymbolTable<MethodDescriptor> InterfaceDescriptor::getMethods() const {
        return this->methods;
    }

    void InterfaceDescriptor::setMethods(SymbolTable<MethodDescriptor> methods) {
        this->methods = methods;
    }

    std::vector<Ptr<InterfaceDescriptor>> InterfaceDescriptor::getInterfaces() const {
        return this->interfaces;
    }

    void InterfaceDescriptor::setInterfaces(std::vector<Ptr<InterfaceDescriptor>> interfaces) {
        this->interfaces = interfaces;
    }

    std::optional<Ptr<FieldDescriptor>> InterfaceDescriptor::findField(std::string name) const {
        if (this->fields.contains(name)) {
            return this->fields[name];
        }

        for (const auto &interface : this->interfaces) {
            std::optional<Ptr<FieldDescriptor>> field = interface->findField(name);

            if (field.has_value()) {
                return field;
            }
        }

        return std::nullopt;
    }

    bool InterfaceDescriptor::containsField(std::string name) const {
        return this->findField(name) != std::nullopt;
    }
}
