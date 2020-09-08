#include <ionir/passes/type_system/borrow_check_pass.h>

namespace ionir {
    BorrowCheckPass::BorrowCheckPass() :
        // TODO: Temporarily passing in
        Pass(PassContext(nullptr)) {
        //
    }
}
