#pragma once

#include <string>

namespace ionir {
    class Named {
    private:
        std::string id;

    public:
        explicit Named(std::string id);

        std::string getId() const;

        void setId(std::string id);
    };
}
