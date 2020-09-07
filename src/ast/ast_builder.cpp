#include <ionir/construct/type/void_type.h>
#include <ionir/syntax/ast_builder.h>
#include <ionir/const/const.h>

namespace ionir {
    void AstBuilder::setBasicBlockBuffer(const ionshared::OptPtr<BasicBlock> &basicBlockBuffer) {
        if (!basicBlockBuffer.has_value()) {
            this->basicBlockBuffer = std::nullopt;
            this->instBuilder = std::nullopt;

            return;
        }

        this->basicBlockBuffer = basicBlockBuffer;
        this->instBuilder = std::make_shared<InstBuilder>(*this->basicBlockBuffer);
    }

    void AstBuilder::require(const ionshared::OptPtr<Construct> &construct) const {
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

    AstBuilder::AstBuilder() :
        ast({}) {
        //
    }

    Ast AstBuilder::make() const noexcept {
        return this->ast;
    }

    AstBuilder &AstBuilder::module(const std::string &id) {
        ionshared::Ptr<Module> module = std::make_shared<Module>(id);

        this->clearBuffers();
        this->moduleBuffer = module;
        this->ast.push_back(module);

        return *this;
    }

    AstBuilder &AstBuilder::function(const std::string &id) {
        this->requireModule();

        // Parent will be filled in below.
        ionshared::Ptr<FunctionBody> functionBody = std::make_shared<FunctionBody>(nullptr);

        ionshared::Ptr<BasicBlock> entrySection = std::make_shared<BasicBlock>(BasicBlockOpts{
            functionBody,
            BasicBlockKind::Entry,
            Const::basicBlockEntryId
        });

        functionBody->insertBasicBlock(entrySection);
        this->setBasicBlockBuffer(entrySection);

        ionshared::Ptr<Type> returnType = std::make_shared<VoidType>();
        ionshared::Ptr<Args> args = std::make_shared<Args>();
        ionshared::Ptr<Prototype> prototype = std::make_shared<Prototype>(id, args, returnType, *this->moduleBuffer);
        ionshared::Ptr<Function> function = std::make_shared<Function>(prototype, functionBody);

        // Fill in the function body's parent.
        functionBody->setParent(function);
        
        this->functionBuffer = function;
        this->moduleBuffer->get()->insertFunction(function);

        return *this;
    }

    AstBuilder &AstBuilder::functionReturnType(ionshared::Ptr<Type> returnType) {
        this->requireFunction();
        this->functionBuffer->get()->getPrototype()->setReturnType(std::move(returnType));

        return *this;
    }

    AstBuilder &AstBuilder::instAlloca(const std::string &id, ionshared::Ptr<Type> type) {
        this->requireBasicBlock();
        this->instBuilder->get()->createAlloca(id, std::move(type));

        return *this;
    }
}
