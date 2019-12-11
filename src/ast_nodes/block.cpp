#include "block.h"
#include "passes/pass.h"

namespace ionir
{
Block::Block(std::vector<std::shared_ptr<Section>> sections)
    : Node(NodeKind::Block), sections(sections), cachedEntry(std::nullopt)
{
    //
}

Block::~Block()
{
    // TODO
}

std::shared_ptr<Node> Block::accept(Pass *visitor)
{
    return visitor->visitBlock(this);
}

bool Block::verify() const
{
    bool entryFound = false;

    /**
     * Loop through all sections to determine
     * whether multiple entry sections exist.
     */
    for (const auto section : this->sections)
    {
        if (section->getKind() == SectionKind::Entry)
        {
            // Multiple entry sections exist.
            if (entryFound)
            {
                return false;
            }

            // Raise the flag.
            entryFound = true;
        }
    }

    return true;
}

std::optional<std::shared_ptr<Section>> Block::getEntrySection()
{
    /**
     * Entry section has already been previously
     * found, return the cached value.
     */
    if (this->cachedEntry.has_value())
    {
        return *this->cachedEntry;
    }

    for (auto section : this->sections)
    {
        if (section->getKind() == SectionKind::Entry)
        {
            // Save the result for faster subsequent access.
            this->cachedEntry = section;

            return this->cachedEntry;
        }
    }

    // Entry section was neither cached nor found.
    return std::nullopt;
}

std::vector<std::shared_ptr<Section>> Block::getSections() const
{
    return this->sections;
}

void Block::setSections(std::vector<std::shared_ptr<Section>> sections)
{
    this->sections = sections;
}
} // namespace ionir
