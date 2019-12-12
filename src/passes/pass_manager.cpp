#include <vector>
#include "parsing/driver.h"
#include "parsing/ast.h"
#include "code_gen/node_kind.h"
#include "pass_manager.h"

namespace ionir
{
PassManager::PassManager() : passes({})
{
    //
}

void PassManager::visitAstNode(std::shared_ptr<Node> node, Pass *visitor)
{
    switch (node->getNodeKind())
    {
    case NodeKind::Block:
    {
        visitor->visitBlock(node->staticCast<Block>());
    }

    case NodeKind::Extern:
    {
        visitor->visitExtern(node->staticCast<Extern>());
    }

    case NodeKind::Function:
    {
        visitor->visitFunction(node->staticCast<Function>());
    }

    case NodeKind::GlobalVariable:
    {
        visitor->visitGlobalVar(node->staticCast<GlobalVar>());
    }

    case NodeKind::IfStatement:
    {
        // TODO: Not yet implemented in Pass.
        throw std::runtime_error("Not yet implemented");
    }

    case NodeKind::Instruction:
    {
        visitor->visitInst(node->staticCast<Inst>());
    }

    case NodeKind::Prototype:
    {
        visitor->visitPrototype(node->staticCast<Prototype>());
    }

    case NodeKind::Section:
    {
        visitor->visitSection(node->staticCast<Section>());
    }

    case NodeKind::Type:
    {
        visitor->visitType(node->staticCast<Type>());
    }

    case NodeKind::Value:
    {
        visitor->visitValue(node->staticCast<Value>());
    }

    default:
    {
        throw std::runtime_error("Unknown node kind");
    }
    }
}

bool PassManager::registerPass(std::unique_ptr<PassManagerItem> item)
{
    auto insertionResult = this->passes.insert(item);

    return insertionResult.second;
}

void PassManager::run()
{
    // TODO: Driver is nullptr;
    Driver *driver = nullptr;

    Ast ast = driver->consume();

    for (auto item : this->passes)
    {
        // TODO: Process priorities.
        for (auto node : ast)
        {
            this->visitAstNode(node, item->pass);
        }
    }
}
} // namespace ionir
