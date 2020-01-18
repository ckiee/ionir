#include <ionir/construct/type/void_type.h>
#include <ionir/misc/ast_builder.h>
#include <ionir/const/const.h>

namespace ionir {
    void AstBuilder::setSectionBuffer(OptPtr<Section> sectionBuffer) {
        if (!sectionBuffer.has_value()) {
            this->sectionBuffer = std::nullopt;
            this->instBuilder = std::nullopt;

            return;
        }

        this->sectionBuffer = sectionBuffer;
        this->instBuilder = std::make_shared<InstBuilder>(*this->sectionBuffer);
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

    void AstBuilder::requireBlock() const {
        this->requireFunction();
        this->require(this->blockBuffer);
    }

    void AstBuilder::requireSection() const {
        this->requireBlock();
        this->require(this->sectionBuffer);
    }

    void AstBuilder::clearBuffers() {
        this->moduleBuffer = std::nullopt;
        this->functionBuffer = std::nullopt;
        this->blockBuffer = std::nullopt;
        setSectionBuffer(std::nullopt);
    }

    Ptr<AstBuilder> AstBuilder::make() {
        return std::make_shared<AstBuilder>();
    }

    AstBuilder::AstBuilder() : ast({}) {
        //
    }

    Ast AstBuilder::getAst() const {
        return this->ast;
    }

    Ptr<AstBuilder> AstBuilder::module(std::string id) {
        Ptr<Module> module = std::make_shared<Module>(id);

        this->clearBuffers();
        this->moduleBuffer = module;

        return this->shared_from_this();
    }

    Ptr<AstBuilder> AstBuilder::function(std::string id) {
        this->requireModule();

        Ptr<Block> block = std::make_shared<Block>(nullptr);

        Ptr<Section> entrySection = std::make_shared<Section>(SectionOpts{
            block,
            SectionKind::Entry,
            Const::sectionEntryId
        });

        (*block->getSymbolTable())[entrySection->getId()] = entrySection;
        this->setSectionBuffer(entrySection);

        Ptr<Type> returnType = std::make_shared<VoidType>();
        Ptr<Args> args = std::make_shared<Args>();
        Ptr<Prototype> prototype = std::make_shared<Prototype>(id, args, returnType);
        Ptr<Function> function = std::make_shared<Function>(prototype, block);

        block->setParent(function);
        this->functionBuffer = function;

        return this->shared_from_this();
    }

    Ptr<AstBuilder> AstBuilder::functionReturnType(Ptr<Type> returnType) {
        this->requireFunction();
        this->functionBuffer->get()->getPrototype()->setReturnType(returnType);

        return this->shared_from_this();
    }

    Ptr<AstBuilder> AstBuilder::instAlloca(std::string id, Ptr<Type> type) {
        this->requireSection();
        this->instBuilder->get()->createAlloca(id, type);

        return this->shared_from_this();
    }
}
