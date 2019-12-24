#include "misc/util.h"
#include "passes/pass.h"
#include "construct/construct_kind.h"
#include "section.h"

namespace ionir {
    Section::Section(SectionOpts opts)
            : ChildConstruct(opts.parent, ConstructKind::Section), kind(opts.kind), id(opts.id), insts(opts.insts) {
        //
    }

    void Section::accept(Pass *visitor) {
        visitor->visitSection(this->cast<Section>());
    }

    SectionKind Section::getKind() const {
        return this->kind;
    }

    std::string Section::getId() const {
        return this->id;
    }

    void Section::setId(std::string id) {
        this->id = id;
    }

    std::vector<Ptr<Inst>> &Section::getInsts() {
        return this->insts;
    }

    void Section::setInsts(std::vector<Ptr<Inst>> insts) {
        this->insts = insts;
    }

    uint32_t Section::relocateInsts(Ptr<Section> target, uint32_t from) {
        uint32_t count = 0;

        for (uint32_t i = from; i < this->insts.size(); i++) {
            target->getInsts().push_back(this->insts[i]);
            this->insts.erase(this->insts.begin() + i - 1);
            count++;
        }

        return count;
    }

    std::optional<uint32_t> Section::locate(Ptr<Inst> inst) {
        return Util::locateInVector<Ptr<Inst>>(this->insts, inst);
    }
}
