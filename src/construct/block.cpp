#include <ionir/construct/function.h>
#include <ionir/passes/pass.h>

namespace ionir {
    Block::Block(Ptr<Function> parent, PtrSymbolTable<Section> symbolTable)
        : ChildConstruct(parent, ConstructKind::Block), ScopeAnchor<Section>(symbolTable), cachedEntry(std::nullopt) {
        //
    }

    void Block::accept(Pass &visitor) {
        visitor.visitBlock(this->cast<Block>());
    }

    Ast Block::getChildNodes() const {
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return Construct::convertChildren(*this->getSymbolTable());
    }

    bool Block::verify() const {
        bool entryFound = false;

        /**
         * Loop through all sections to determine
         * whether multiple entry sections exist.
         */
        for (const auto &[key, section] : this->getSymbolTable()->unwrap()) {
            if (section->getKind() == SectionKind::Entry) {
                // Multiple entry sections exist.
                if (entryFound) {
                    return false;
                }

                // Raise the flag.
                entryFound = true;
            }
                // A section failed to verify.
            else if (!section->verify()) {
                return false;
            }
        }

        return true;
    }

    std::optional<Ptr<Section>> Block::getEntrySection() {
        /**
         * Entry section has already been previously
         * found, return the cached value.
         */
        if (this->cachedEntry.has_value()) {
            return *this->cachedEntry;
        }

        for (const auto &[key, section] : this->getSymbolTable()->unwrap()) {
            if (section->getKind() == SectionKind::Entry) {
                // Save the result for faster subsequent access.
                this->cachedEntry = section;

                return this->cachedEntry;
            }
        }

        // Entry section was neither cached nor found.
        return std::nullopt;
    }
}
