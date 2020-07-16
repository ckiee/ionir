#include <ionir/tracking/interface_descriptor.h>

namespace ionir {
    std::string InterfaceDescriptor::getName() const {
        return this->name;
    }

    void InterfaceDescriptor::setName(std::string name) {
        this->name = name;
    }

    PtrSymbolTable<FieldDescriptor> InterfaceDescriptor::getFields() const {
        return this->fields;
    }

    void InterfaceDescriptor::setFields(PtrSymbolTable<FieldDescriptor> fields) {
        this->fields = fields;
    }

    //    PtrSymbolTable<MethodDescriptor> InterfaceDescriptor::getMethods() const {
    //        return this->methods;
    //    }
    //
    //    void InterfaceDescriptor::setMethods(PtrSymbolTable<MethodDescriptor> methods) {
    //        this->methods = methods;
    //    }

    std::vector<ionshared::Ptr<InterfaceDescriptor>> InterfaceDescriptor::getInterfaces() const {
        return this->interfaces;
    }

    void InterfaceDescriptor::setInterfaces(std::vector<ionshared::Ptr<InterfaceDescriptor>> interfaces) {
        this->interfaces = interfaces;
    }

    std::optional<ionshared::Ptr<FieldDescriptor>> InterfaceDescriptor::findField(std::string name) {
        if (this->fields->contains(name)) {
            return (*this->fields)[name];
        }

        for (const auto &interface : this->interfaces) {
            std::optional<ionshared::Ptr<FieldDescriptor>> field = interface->findField(name);

            if (field.has_value()) {
                return field;
            }
        }

        return std::nullopt;
    }

    bool InterfaceDescriptor::containsField(std::string name) {
        return this->findField(name) != std::nullopt;
    }
}
