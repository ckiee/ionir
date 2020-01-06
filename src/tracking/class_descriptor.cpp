#include <ionir/tracking/class_descriptor.h>

namespace ionir {
    std::optional<Ptr<MethodDescriptor>> ClassDescriptor::findMethod(std::string name) {
        SymbolTable<MethodDescriptor> localMethods = this->getMethods();

        if (localMethods.contains(name)) {
            return localMethods[name];
        }
        else if (this->parent.has_value()) {
            return this->parent->get()->findMethod(name);
        }

        return std::nullopt;
    }

    bool ClassDescriptor::containsMethod(std::string name) {
        return this->findMethod(name) != std::nullopt;
    }
}
