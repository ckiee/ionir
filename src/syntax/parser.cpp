#include <utility>
#include <vector>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    Classifier Parser::getClassifier() const noexcept {
        return this->classifier;
    }

    bool Parser::is(TokenKind tokenKind) noexcept {
        return this->stream.get().getKind() == tokenKind;
    }

    bool Parser::isNext(TokenKind tokenKind) {
        return this->stream.peek()->getKind() == tokenKind;
    }

    bool Parser::expect(TokenKind tokenKind) {
        if (!this->is(tokenKind)) {
            this->makeNotice("Expected token kind: " + std::to_string((int)tokenKind) + ", but got: " +
                std::to_string((int)this->stream.get().getKind()));

            return false;
        }

        return true;
    }

    bool Parser::skipOver(TokenKind tokenKind) {
        if (!this->expect(tokenKind)) {
            return false;
        }

        this->stream.skip();

        return true;
    }

    ionshared::NoticeFactory Parser::createNoticeFactory() noexcept {
        // Abstract current Token for easier access.
        Token token = this->stream.get();

        return ionshared::NoticeFactory(ionshared::NoticeContext{
            this->filePath,
            token.getLineNumber(),
            token.getStartPosition()
        });
    }

    std::nullopt_t Parser::makeNotice(std::string message, ionshared::NoticeType type) {
        this->noticeStack->push(this->createNoticeFactory().make(type, std::move(message)));

        return std::nullopt;
    }

    Parser::Parser(TokenStream stream, const ionshared::Ptr<ionshared::NoticeStack> &noticeStack, std::string filePath)
        : stream(std::move(stream)), noticeStack(noticeStack), noticeSentinel(std::make_shared<NoticeSentinel>(noticeStack)), filePath(std::move(filePath)), classifier() {
        //
    }

    ionshared::Ptr<ionshared::NoticeStack> Parser::getNoticeStack() const {
        return this->noticeStack;
    }

    std::string Parser::getFilePath() const {
        return this->filePath;
    }

    AstPtrResult<> Parser::parseTopLevel(const ionshared::Ptr<Module> &parent) {
        switch (this->stream.get().getKind()) {
            case TokenKind::KeywordFunction: {
                return Util::convertAstPtrResult(this->parseFunction(parent));
            }

            case TokenKind::KeywordGlobal: {
                return Util::convertAstPtrResult(this->parseGlobal());
            }

            case TokenKind::KeywordExtern: {
                return Util::convertAstPtrResult(this->parseExtern(parent));
            }

            default: {
                return this->noticeSentinel->makeError(
                    IONIR_NOTICE_MISC_UNEXPECTED_TOKEN
                );
            }
        }
    }

    AstPtrResult<Global> Parser::parseGlobal() {
        this->assertOrError(this->skipOver(TokenKind::KeywordGlobal));

        AstPtrResult<Type> type = this->parseType();

        this->assertHasValue(type);

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);

        // TODO: Handle in-line initialization & pass std::optional<Value> into Global constructor.

        this->assertOrError(this->skipOver(TokenKind::SymbolSemiColon));

        return std::make_shared<Global>(Util::getResultPtrValue(type), *id);
    }

    AstPtrResult<BasicBlock> Parser::parseBasicBlock(ionshared::Ptr<FunctionBody> parent) {
        this->assertOrError(this->skipOver(TokenKind::SymbolAt));

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);
        this->assertOrError(this->skipOver(TokenKind::SymbolColon));
        this->assertOrError(this->skipOver(TokenKind::SymbolBraceL));

        // Determine the section's kind.
        BasicBlockKind kind = BasicBlockKind::Label;

        // TODO: Id cannot possibly start with the internal prefix since parseId() does not support '.' on an id!

        if (*id == Const::basicBlockEntryId) {
            kind = BasicBlockKind::Entry;
        }
        else if (ionshared::Util::stringStartsWith(*id, Const::basicBlockInternalPrefix)) {
            kind = BasicBlockKind::Internal;
        }

        ionshared::Ptr<BasicBlock> basicBlock = std::make_shared<BasicBlock>(BasicBlockOpts{
            std::move(parent),
            kind,
            *id
        });

        std::vector<ionshared::Ptr<RegisterAssign>> registers = {};
        std::vector<ionshared::Ptr<Inst>> insts = {};
        PtrSymbolTable<Inst> symbolTable = basicBlock->getSymbolTable();

        while (!this->is(TokenKind::SymbolBraceR) && !this->is(TokenKind::SymbolAt)) {
            ionshared::OptPtr<Inst> inst = std::nullopt;

            // TODO: This means that allocas without register assigns are possible (lonely, redundant allocas).
            // Register assignment. This includes an instruction.
            if (this->is(TokenKind::OperatorModulo)) {
                AstPtrResult<RegisterAssign> registerAssignResult = this->parseRegisterAssign(basicBlock);

                this->assertHasValue(registerAssignResult);

                ionshared::Ptr<RegisterAssign> registerAssign = Util::getResultPtrValue(registerAssignResult);

                inst = registerAssign->getValue()->dynamicCast<Inst>();

                /**
                 * Register the instruction on the resulting block's symbol
                 * table.
                 */
                symbolTable->insert(registerAssign->getId(), *inst);

                /**
                 * Add the register to the block's registers to be processed
                 * later for code-gen.
                 */
                registers.push_back(registerAssign);
            }
            // Otherwise, it must be just an instruction.
            else {
                inst = this->parseInst(basicBlock);
            }

            this->assertHasValue(inst);
            insts.push_back(*inst);
        }

        this->stream.skip();
        basicBlock->setRegisters(registers);
        basicBlock->setInsts(insts);

        return basicBlock;
    }

    AstPtrResult<FunctionBody> Parser::parseFunctionBody(const ionshared::Ptr<Function> &parent) {
        this->assertOrError(this->skipOver(TokenKind::SymbolBraceL));

        ionshared::Ptr<FunctionBody> functionBody = std::make_shared<FunctionBody>(parent);
        PtrSymbolTable<BasicBlock> basicBlocks = std::make_shared<ionshared::SymbolTable<ionshared::Ptr<BasicBlock>>>();

        while (!this->is(TokenKind::SymbolBraceR)) {
            AstPtrResult<BasicBlock> basicBlockResult = this->parseBasicBlock(functionBody);

            this->assertHasValue(basicBlockResult);

            ionshared::Ptr<BasicBlock> basicBlock = Util::getResultPtrValue(basicBlockResult);

            basicBlocks->insert(basicBlock->getId(), basicBlock);
        }

        functionBody->setSymbolTable(basicBlocks);

        // Skip over right brace token.
        this->stream.skip();

        return functionBody;
    }

    AstPtrResult<Module> Parser::parseModule() {
        this->assertOrError(this->skipOver(TokenKind::KeywordModule));

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);
        this->assertOrError(this->skipOver(TokenKind::SymbolBraceL));

        PtrSymbolTable<Construct> symbolTable =
            std::make_shared<ionshared::SymbolTable<ionshared::Ptr<Construct>>>();

        ionshared::Ptr<Module> module = std::make_shared<Module>(*id, symbolTable);

        while (!this->is(TokenKind::SymbolBraceR)) {
            AstPtrResult<> topLevelConstructResult = this->parseTopLevel(module);

            // TODO: Make notice if it has no value? Or is it enough with the notice under 'parseTopLevel()'?
            if (Util::hasValue(topLevelConstructResult)) {
                ionshared::Ptr<Construct> topLevelConstruct = Util::getResultPtrValue(topLevelConstructResult);
                std::optional<std::string> name = Util::getConstructId(topLevelConstruct);

                if (!name.has_value()) {
                    throw std::runtime_error("Unexpected construct name to be null");
                }

                // TODO: Ensure we're not re-defining something, issue a notice otherwise.
                symbolTable->insert(*name, topLevelConstruct);
            }

            // No more tokens to process.
            if (!this->stream.hasNext() && !this->is(TokenKind::SymbolBraceR)) {
                return this->noticeSentinel->makeError<Module>(IONIR_NOTICE_MISC_UNEXPECTED_EOF);
            }
        }

        this->assertOrError(this->skipOver(TokenKind::SymbolBraceR));

        return module;
    }

    AstPtrResult<RegisterAssign> Parser::parseRegisterAssign(const ionshared::Ptr<BasicBlock> &parent) {
        this->assertOrError(this->skipOver(TokenKind::OperatorModulo));

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);
        this->assertOrError(this->skipOver(TokenKind::SymbolEqual));

        AstPtrResult<Inst> inst = this->parseInst(parent);

        this->assertHasValue(inst);

        return std::make_shared<RegisterAssign>(*id, Util::getResultPtrValue(inst));
    }

    std::optional<std::string> Parser::parseLine() {
        // TODO: Lexer cannot ignore whitespace.
        return "";
    }

    std::optional<Directive> Parser::parseDirective() {
        this->assertOrError(this->skipOver(TokenKind::SymbolHash));

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);

        std::optional<std::string> content = this->parseLine();

        return std::make_pair(*id, content);
    }
}
