#include <ionir/misc/named.h>

namespace ionir {
    Named::Named(std::string id) : id(id) {
        //
    }

    std::string Named::getId() const {
        return this->id;
    }

    void Named::setId(std::string id) {
        this->id = id;
    }
}
