#include "const/token_const.h"
#include "const/const.h"
#include "static_init.h"

namespace ionir
{
bool StaticInit::init()
{
    TokenConst::init();

    return Const::init();
}
} // namespace ionir
