#include <ionir/const/const.h>
#include <ionir/tracking/name_mangler.h>

namespace ionir {
    std::string NameMangler::internal(std::string id) {
        return Const::basicBlockInternalPrefix + id;
    }
}
