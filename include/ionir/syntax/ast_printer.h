#pragma once

#include <sstream>
#include <vector>
#include <ionir/construct/construct.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    struct AstPrinterTreeNode {
        uint32_t depth;

        bool isLeaf;

        Ptr<Construct> construct;
    };

    class AstPrinter {
    private:
        const Ast &ast;

        std::stringstream tree;

        uint32_t depth;

    protected:
        void visitNode(AstPrinterTreeNode node);

    public:
        static std::string makeSpaces(uint32_t depth);

        AstPrinter(const Ast &ast);

        std::optional<std::string> make();

        void reset();
    };
}
