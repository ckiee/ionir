#include <queue>
#include <sstream>
#include <ionir/syntax/ast_printer.h>

namespace ionir {
    std::string AstPrinter::makeSpaces(uint32_t depth) {
        std::stringstream spaces;

        for (uint32_t i = 0; i < depth; i++) {
            spaces << " ";
        }

        return spaces.str();
    }

    AstPrinter::AstPrinter(const Ast &ast) : ast(ast) {
        //
    }

    std::optional<std::string> AstPrinter::getTreeString() const {
        if (this->ast.empty()) {
            return std::nullopt;
        }

        uint32_t depth = 0;
        std::queue<TreeQueueNode> queue = {};
        std::stringstream tree;

        for (const auto construct : this->ast) {
            queue.push(TreeQueueNode{
                depth,
                construct
            });
        }

        while (!queue.empty()) {
            TreeQueueNode node = queue.front();

            queue.pop();

            for (const auto child : node.construct->getChildNodes()) {
                queue.push(TreeQueueNode{
                    depth + 1,
                    child
                });
            }

            tree << AstPrinter::makeSpaces(depth) << (int)node.construct->getConstructKind() << std::endl;
        }

        std::string treeString = tree.str();

        if (treeString == "") {
            return std::nullopt;
        }

        return treeString;
    }
}
