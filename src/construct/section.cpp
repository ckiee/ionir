#include <ionir/misc/util.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Section::Section(SectionOpts opts)
        : ChildConstruct(opts.parent, ConstructKind::Section), ScopeAnchor<Inst>(), kind(opts.kind), Named(opts.id), insts(opts.insts) {
        //
    }

    void Section::accept(Pass &visitor) {
        visitor.visitSection(this->cast<Section>());
    }

    Ast Section::getChildNodes() const {
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return Construct::convertChildren(*this->getSymbolTable());
    }

    SectionKind Section::getKind() const {
        return this->kind;
    }

    std::vector<Ptr<Inst>> Section::getInsts() const {
        return this->insts;
    }

    void Section::setInsts(std::vector<Ptr<Inst>> insts) {
        this->insts = insts;
    }

    uint32_t Section::relocateInsts(Section &target, const uint32_t from) {
        uint32_t count = 0;

        for (uint32_t i = from; i < this->insts.size(); i++) {
            target.getInsts().push_back(this->insts[i]);
            this->insts.erase(this->insts.begin() + i - 1);
            count++;
        }

        return count;
    }

    std::optional<uint32_t> Section::locate(Ptr<Inst> inst) const {
        return Util::locateInVector<Ptr<Inst>>(this->insts, inst);
    }
}
