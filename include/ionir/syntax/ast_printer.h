#pragma once

#include <vector>
#include <ionir/construct/construct.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    struct TreeQueueNode {
        uint32_t depth;

        Ptr<Construct> construct;
    };

    class AstPrinter {
    private:
        const Ast &ast;

    public:
        static std::string makeSpaces(uint32_t depth);

        AstPrinter(const Ast &ast);

        std::optional<std::string> getTreeString() const;
    };
}
