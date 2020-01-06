#pragma once

#include "interface_descriptor.h"

namespace ionir {
    class ClassDescriptor : public InterfaceDescriptor {
    private:
        std::optional<Ptr<ClassDescriptor>> parent;

    public:
        std::optional<Ptr<MethodDescriptor>> findMethod(std::string name);

        bool containsMethod(std::string name);
    };
}
