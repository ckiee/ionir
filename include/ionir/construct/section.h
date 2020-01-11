#pragma once

#include <optional>
#include <string>
#include <vector>
#include <ionir/misc/helpers.h>
#include "pseudo/args.h"
#include "inst.h"
#include "child_construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    class Block;

    enum class SectionKind {
        /**
         * The entry section of a block.
         */
            Entry,

        /**
         * A section defined by the user. Can be jumped to
         * using a goto instruction.
         */
            Label,

        /**
         * A section which forms part of a construct. Cannot be
         * directly accessed by the user.
         */
            Internal
    };

    struct SectionOpts : ChildConstructOpts<Block> {
        SectionKind kind;

        std::string id;

        std::vector<Ptr<Inst>> insts = {};

        PtrSymbolTable<Inst> symbolTable = {};
    };

    class Section : public ChildConstruct<Block> {
    private:
        SectionKind kind;

        std::string id;

        std::vector<Ptr<Inst>> insts;

        PtrSymbolTable<Inst> symbolTable;

    public:
        explicit Section(SectionOpts opts);

        void accept(Pass &visitor) override;

        Ast getChildNodes() const override;

        SectionKind getKind() const;

        std::string getId() const;

        void setId(const std::string id);

        std::vector<Ptr<Inst>> getInsts() const;

        void setInsts(std::vector<Ptr<Inst>> insts);

        uint32_t relocateInsts(Section &target, uint32_t from = 0);

        /**
         * Attempt to find the index location
         * of an instruction. Returns null if
         * not found.
         */
        std::optional<uint32_t> locate(Ptr<Inst> inst) const;

        PtrSymbolTable<Inst> getSymbolTable() const;

        void setSymbolTable(PtrSymbolTable<Inst> symbolTable);
    };
}
