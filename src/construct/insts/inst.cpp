#include "construct/section.h"
#include "passes/pass.h"
#include "inst.h"

namespace ionir {
    Inst::Inst(Ptr<Section> parent, InstKind kind)
        : ChildConstruct(parent, ConstructKind::Instruction), kind(kind) {
        //
    }

    InstKind Inst::getInstKind() const {
        return this->kind;
    }
}
