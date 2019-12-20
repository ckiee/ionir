#include "constants/constants.h"
#include "name_mangler.h"

namespace ionir
{
std::string NameMangler::internal(std::string id)
{
    return Const::sectionInternalPrefix + id;
}
} // namespace ionir
