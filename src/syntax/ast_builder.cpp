#include <ionir/construct/type/void_type.h>
#include <ionir/syntax/ast_builder.h>
#include <ionir/const/const.h>

namespace ionir {
    void AstBuilder::setBasicBlockBuffer(OptPtr<BasicBlock> basicBlockBuffer) {
        if (!basicBlockBuffer.has_value()) {
            this->basicBlockBuffer = std::nullopt;
            this->instBuilder = std::nullopt;

            return;
        }

        this->basicBlockBuffer = basicBlockBuffer;
        this->instBuilder = std::make_shared<InstBuilder>(*this->basicBlockBuffer);
    }

    void AstBuilder::require(OptPtr<Construct> construct) const {
        if (!construct.has_value()) {
            throw std::runtime_error("Required construct is null");
        }
    }

    void AstBuilder::requireModule() const {
        this->require(this->moduleBuffer);
    }

    void AstBuilder::requireFunction() const {
        this->requireModule();
        this->require(this->functionBuffer);
    }

    void AstBuilder::requireFunctionBody() const {
        this->requireFunction();
        this->require(this->blockBuffer);
    }

    void AstBuilder::requireBasicBlock() const {
        this->requireFunctionBody();
        this->require(this->basicBlockBuffer);
    }

    void AstBuilder::clearBuffers() {
        this->moduleBuffer = std::nullopt;
        this->functionBuffer = std::nullopt;
        this->blockBuffer = std::nullopt;
        setBasicBlockBuffer(std::nullopt);
    }

    AstBuilder::AstBuilder() : ast({}) {
        //
    }

    Ast AstBuilder::make() const noexcept {
        return this->ast;
    }

    AstBuilder &AstBuilder::module(std::string id) {
        Ptr<Module> module = std::make_shared<Module>(id);

        this->clearBuffers();
        this->moduleBuffer = module;
        this->ast.push_back(module);

        return *this;
    }

    AstBuilder &AstBuilder::function(std::string id) {
        this->requireModule();

        Ptr<FunctionBody> block = std::make_shared<FunctionBody>(nullptr);

        Ptr<BasicBlock> entrySection = std::make_shared<BasicBlock>(BasicBlockOpts{
            block,
            BasicBlockKind::Entry,
            Const::basicBlockEntryId
        });

        block->insertBasicBlock(entrySection);
        this->setBasicBlockBuffer(entrySection);

        Ptr<Type> returnType = std::make_shared<VoidType>();
        Ptr<Args> args = std::make_shared<Args>();
        Ptr<Prototype> prototype = std::make_shared<Prototype>(id, args, returnType, *this->moduleBuffer);
        Ptr<Function> function = std::make_shared<Function>(prototype, block);

        block->setParent(function);
        this->functionBuffer = function;
        this->moduleBuffer->get()->insertFunction(function);

        return *this;
    }

    AstBuilder &AstBuilder::functionReturnType(Ptr<Type> returnType) {
        this->requireFunction();
        this->functionBuffer->get()->getPrototype()->setReturnType(returnType);

        return *this;
    }

    AstBuilder &AstBuilder::instAlloca(std::string id, Ptr<Type> type) {
        this->requireBasicBlock();
        this->instBuilder->get()->createAlloca(id, type);

        return *this;
    }
}
