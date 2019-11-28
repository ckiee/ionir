#pragma once

namespace ionir
{
enum class SectionKind
{
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
}
