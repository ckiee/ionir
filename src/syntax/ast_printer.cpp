#include <string>
#include <optional>
#include <queue>
#include <sstream>
#include <ionir/syntax/ast_printer.h>

#define IONIR_TREE_V_LINE "│"
#define IONIR_TREE_H_LINE "─"
#define IONIR_TREE_INTERSECTION "├"
#define IONIR_TREE_LEAF "└"

namespace ionir {
    void AstPrinter::visitNode(AstPrinterTreeNode node) {
        if (this->depth != 0) {
            this->tree << IONIR_TREE_V_LINE << AstPrinter::makeSpaces(2);
        }

        std::string type = node.isLeaf ? IONIR_TREE_LEAF : IONIR_TREE_INTERSECTION;
        std::optional<std::string> constructName = node.construct->getConstructName();

        tree << type
            << IONIR_TREE_H_LINE
            << IONIR_TREE_H_LINE
            << AstPrinter::makeSpaces(node.depth)
            << constructName.value_or("Unnamed")
            << std::endl;
    }

    std::string AstPrinter::makeSpaces(uint32_t depth) {
        std::stringstream spaces;

        for (uint32_t i = 0; i < depth; i++) {
            spaces << " ";
        }

        return spaces.str();
    }

    AstPrinter::AstPrinter(const Ast &ast) : ast(ast), depth(0) {
        //
    }

    std::optional<std::string> AstPrinter::make() {
        if (this->ast.empty()) {
            return std::nullopt;
        }

        uint32_t depth = 0;
        std::queue<AstPrinterTreeNode> queue = {};
        std::stringstream tree;

        for (const auto construct : this->ast) {
            queue.push(AstPrinterTreeNode{
                depth,
                construct->isLeafNode(),
                construct
            });
        }

        while (!queue.empty()) {
            AstPrinterTreeNode node = queue.front();

            queue.pop();
            depth = node.depth;

            for (const auto child : node.construct->getChildNodes()) {
                queue.push(AstPrinterTreeNode{
                    depth + 1,
                    child->isLeafNode(),
                    child
                });
            }

            this->visitNode(node);
        }

        std::string treeString = this->tree.str();

        if (treeString == "") {
            return std::nullopt;
        }

        return treeString;
    }

    void AstPrinter::reset() {
        this->depth = 0;
        this->tree.clear();
    }
}
