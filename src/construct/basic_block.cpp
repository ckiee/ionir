#include <ionir/misc/inst_builder.h>
#include <ionir/passes/pass.h>

namespace ionir {
    BasicBlock::BasicBlock(const BasicBlockOpts &opts)
        : ChildConstruct(opts.parent, ConstructKind::BasicBlock),
            ScopeAnchor<Inst>(),
            kind(opts.kind),
            Named(opts.id),
            registers(opts.registers),
            insts(opts.insts) {
        //
    }

    void BasicBlock::accept(Pass &visitor) {
        visitor.visitScopeAnchor(this->dynamicCast<ScopeAnchor<>>());
        visitor.visitBasicBlock(this->dynamicCast<BasicBlock>());
    }

    Ast BasicBlock::getChildNodes() {
        return Construct::mergeChildren(
            Construct::convertChildren(this->registers),
            Construct::convertChildren(this->insts)
        );
    }

    BasicBlockKind BasicBlock::getKind() const noexcept {
        return this->kind;
    }

    std::vector<ionshared::Ptr<RegisterAssign>> &BasicBlock::getRegisters() noexcept {
        return this->registers;
    }

    void BasicBlock::setRegisters(std::vector<ionshared::Ptr<RegisterAssign>> registers) {
        this->registers = std::move(registers);
    }

    std::vector<ionshared::Ptr<Inst>> &BasicBlock::getInsts() noexcept {
        return this->insts;
    }

    // TODO: SymbolTable must be re-populated after changing insts vector.
    void BasicBlock::setInsts(std::vector<ionshared::Ptr<Inst>> insts) {
        this->insts = std::move(insts);
    }

    void BasicBlock::insertInst(ionshared::Ptr<Inst> inst) {
        this->insts.push_back(inst);

        std::optional<std::string> id = Util::getInstId(inst);

        // Instruction is named. Register it in the symbol table.
        if (id.has_value()) {
            this->getSymbolTable()->insert(*id, inst);
        }
    }

    uint32_t BasicBlock::relocateInsts(BasicBlock &target, const uint32_t from) {
        uint32_t count = 0;

        for (uint32_t i = from; i < this->insts.size(); i++) {
            target.getInsts().push_back(this->insts[i]);
            this->insts.erase(this->insts.begin() + i - 1);
            count++;
        }

        return count;
    }

    std::optional<uint32_t> BasicBlock::locate(ionshared::Ptr<Inst> inst) const {
        return Util::locateInVector<ionshared::Ptr<Inst>>(this->insts, std::move(inst));
    }

    ionshared::Ptr<InstBuilder> BasicBlock::createBuilder() {
        return std::make_shared<InstBuilder>(this->dynamicCast<BasicBlock>());
    }

    ionshared::OptPtr<Inst> BasicBlock::findTerminalInst() const {
        for (const auto &inst : this->insts) {
            if (inst->isTerminal()) {
                return inst;
            }
        }

        return std::nullopt;
    }
}
