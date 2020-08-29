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

    Parser::Parser(
        TokenStream stream,
        const ionshared::Ptr<ionshared::NoticeStack> &noticeStack,
        std::string filePath
    ) :
        stream(std::move(stream)),
        noticeStack(noticeStack),
        noticeSentinel(std::make_shared<NoticeSentinel>(noticeStack)),
        filePath(std::move(filePath)),
        classifier() {
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
                return util::castAstPtrResult(this->parseFunction(parent));
            }

            case TokenKind::KeywordGlobal: {
                return util::castAstPtrResult(this->parseGlobal());
            }

            case TokenKind::KeywordExtern: {
                return util::castAstPtrResult(this->parseExtern(parent));
            }

            default: {
                return this->noticeSentinel->makeError(
                    IONIR_NOTICE_MISC_UNEXPECTED_TOKEN
                );
            }
        }
    }

    AstPtrResult<Global> Parser::parseGlobal() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordGlobal), Global)

        AstPtrResult<Type> type = this->parseType();

        IONIR_PARSER_ASSERT_RESULT(type, Global)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(id, Global)

        ionshared::OptPtr<Value<>> inlineValue = std::nullopt;

        // TODO: Handle in-line initialization & pass std::optional<Value> into Global constructor.
        if (this->is(TokenKind::SymbolEqual)) {
            IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolEqual), Global)

            AstPtrResult<Value<>> valueResult = this->parseValue();

            IONIR_PARSER_ASSERT_RESULT(valueResult, Global)

            inlineValue = util::getResultValue(valueResult);
        }

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolSemiColon), Global)

        return std::make_shared<Global>(util::getResultValue(type), *id, inlineValue);
    }

    AstPtrResult<BasicBlock> Parser::parseBasicBlock(ionshared::Ptr<FunctionBody> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolAt), BasicBlock)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(id, BasicBlock)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolColon), BasicBlock)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL), BasicBlock)

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
            AstPtrResult<Inst> inst;

            // TODO: This means that allocas without register assigns are possible (lonely, redundant allocas).
            // Register assignment. This includes an instruction.
            if (this->is(TokenKind::OperatorModulo)) {
                AstPtrResult<RegisterAssign> registerAssignResult = this->parseRegisterAssign(basicBlock);

                IONIR_PARSER_ASSERT_RESULT(registerAssignResult, BasicBlock)

                ionshared::Ptr<RegisterAssign> registerAssign = util::getResultValue(registerAssignResult);

                inst = registerAssign->getValue()->dynamicCast<Inst>();

                /**
                 * Register the instruction on the resulting block's symbol
                 * table.
                 */
                symbolTable->insert(registerAssign->getId(), util::getResultValue(inst));

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

            IONIR_PARSER_ASSERT_RESULT(inst, BasicBlock)
            insts.push_back(util::getResultValue(inst));
        }

        this->stream.skip();
        basicBlock->setRegisters(registers);
        basicBlock->setInsts(insts);

        return basicBlock;
    }

    AstPtrResult<FunctionBody> Parser::parseFunctionBody(const ionshared::Ptr<Function> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL), FunctionBody)

        ionshared::Ptr<FunctionBody> functionBody = std::make_shared<FunctionBody>(parent);
        PtrSymbolTable<BasicBlock> basicBlocks = std::make_shared<ionshared::SymbolTable<ionshared::Ptr<BasicBlock>>>();

        while (!this->is(TokenKind::SymbolBraceR)) {
            AstPtrResult<BasicBlock> basicBlockResult = this->parseBasicBlock(functionBody);

            IONIR_PARSER_ASSERT_RESULT(basicBlockResult, FunctionBody)

            ionshared::Ptr<BasicBlock> basicBlock = util::getResultValue(basicBlockResult);

            basicBlocks->insert(basicBlock->getId(), basicBlock);
        }

        functionBody->setSymbolTable(basicBlocks);

        // Skip over right brace token.
        this->stream.skip();

        return functionBody;
    }

    AstPtrResult<Module> Parser::parseModule() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordModule), Module)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(id, Module)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL), Module)

        ionshared::Ptr<Module> module = std::make_shared<Module>(*id);

        while (!this->is(TokenKind::SymbolBraceR)) {
            AstPtrResult<> topLevelConstructResult = this->parseTopLevel(module);

            // TODO: Make notice if it has no value? Or is it enough with the notice under 'parseTopLevel()'?
            if (util::hasValue(topLevelConstructResult)) {
                ionshared::Ptr<Construct> topLevelConstruct = util::getResultValue(topLevelConstructResult);
                std::optional<std::string> name = util::getConstructId(topLevelConstruct);

                if (!name.has_value()) {
                    throw std::runtime_error("Unexpected construct name to be null");
                }

                // TODO: Ensure we're not re-defining something, issue a notice otherwise.
                module->getContext()->getGlobalScope()->insert(*name, topLevelConstruct);
            }

            // No more tokens to process.
            if (!this->stream.hasNext() && !this->is(TokenKind::SymbolBraceR)) {
                return this->noticeSentinel->makeError<Module>(IONIR_NOTICE_MISC_UNEXPECTED_EOF);
            }
        }

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceR), Module)

        return module;
    }

    AstPtrResult<RegisterAssign> Parser::parseRegisterAssign(const ionshared::Ptr<BasicBlock> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::OperatorModulo), RegisterAssign)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(id, RegisterAssign)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolEqual), RegisterAssign)

        AstPtrResult<Inst> inst = this->parseInst(parent);

        IONIR_PARSER_ASSERT_RESULT(inst, RegisterAssign)

        return std::make_shared<RegisterAssign>(*id, util::getResultValue(inst));
    }

    std::optional<std::string> Parser::parseLine() {
        // TODO: Lexer cannot ignore whitespace.
        return "";
    }

    std::optional<Directive> Parser::parseDirective() {
        // TODO: Not specialized to handle std::optional<>. 'IONIR_PARSER_ASSERT'.
//        this->assertOrError(this->skipOver(TokenKind::SymbolHash));

        std::optional<std::string> id = this->parseId();

        // TODO: Not specialized to handle std::optional<>. 'IONIR_PARSER_ASSERT'.
//        this->assertHasValue(id);

        std::optional<std::string> content = this->parseLine();

        return std::make_pair(*id, content);
    }
}
