#include <ionir/misc/inst_builder.h>
#include <ionir/misc/util.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Section::Section(SectionOpts opts)
        : ChildConstruct(opts.parent, ConstructKind::Section), ScopeAnchor<Inst>(), kind(opts.kind), Named(opts.id), insts(opts.insts) {
        //
    }

    void Section::accept(Pass &visitor) {
        visitor.visitScopeAnchor(this->cast<ScopeAnchor<>>());
        visitor.visitSection(this->cast<Section>());
    }

    Ast Section::getChildNodes() const {
        return Construct::convertChildren(this->insts);
    }

    SectionKind Section::getKind() const {
        return this->kind;
    }

    std::vector<Ptr<Inst>> &Section::getInsts() {
        return this->insts;
    }

    // TODO: SymbolTable must be re-populated after changing insts vector.
    void Section::setInsts(std::vector<Ptr<Inst>> insts) {
        this->insts = insts;
    }

    void Section::insertInst(Ptr<Inst> inst) {
        this->insts.push_back(inst);

        std::optional<std::string> id = Util::getInstId(inst);

        // Instruction is named. Register it in the symbol table.
        if (id.has_value()) {
            this->getSymbolTable()->insert(*id, inst);
        }
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

    Ptr<InstBuilder> Section::createBuilder() {
        return std::make_shared<InstBuilder>(this->cast<Section>());
    }
}
