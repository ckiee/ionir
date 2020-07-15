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

    bool Parser::isPeek(TokenKind tokenKind) {
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

    NoticeFactory Parser::createNoticeFactory() noexcept {
        // Abstract current Token for easier access.
        Token token = this->stream.get();

        return NoticeFactory(NoticeContext{
            this->filePath,
            token.getLineNumber(),
            token.getStartPosition()
        });
    }

    std::nullopt_t Parser::makeNotice(std::string message, NoticeType type) {
        this->stackTrace.push_back(this->createNoticeFactory().make(type, message));

        return std::nullopt;
    }

    Parser::Parser(TokenStream stream, StackTrace stackTrace, std::string filePath)
        : stream(stream), stackTrace(stackTrace), filePath(filePath), classifier() {
        //
    }

    StackTrace Parser::getStackTrace() const {
        return this->stackTrace;
    }

    std::string Parser::getFilePath() const {
        return this->filePath;
    }

    OptPtr<Construct> Parser::parseTopLevel(Ptr<Module> parent) {
        switch (this->stream.get().getKind()) {
            case TokenKind::KeywordFunction: {
                return this->parseFunction(parent);
            }

            case TokenKind::KeywordGlobal: {
                return this->parseGlobal();
            }

            case TokenKind::KeywordExtern: {
                return this->parseExtern(parent);
            }

            default: {
                return this->makeNotice("Unknown top-level construct");
            }
        }
    }

    OptPtr<Global> Parser::parseGlobal() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordGlobal))

        OptPtr<Type> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        // TODO: Handle in-line initialization & pass std::optional<Value> into Global constructor.

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolSemiColon))

        return std::make_shared<Global>(*type, *id);
    }

    OptPtr<BasicBlock> Parser::parseBasicBlock(Ptr<FunctionBody> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolAt))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolColon))
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        // Determine the section's kind.
        BasicBlockKind kind = BasicBlockKind::Label;

        // TODO: Id cannot possibly start with the internal prefix since parseId() does not support '.' on an id!

        if (*id == Const::basicBlockEntryId) {
            kind = BasicBlockKind::Entry;
        }
        else if (Util::stringStartsWith(*id, Const::basicBlockInternalPrefix)) {
            kind = BasicBlockKind::Internal;
        }

        Ptr<BasicBlock> basicBlock = std::make_shared<BasicBlock>(BasicBlockOpts{
            parent,
            kind,
            *id
        });

        std::vector<Ptr<RegisterAssign>> registers = {};
        std::vector<Ptr<Inst>> insts = {};
        PtrSymbolTable<Inst> symbolTable = basicBlock->getSymbolTable();

        while (!this->is(TokenKind::SymbolBraceR) && !this->is(TokenKind::SymbolAt)) {
            OptPtr<Inst> inst = std::nullopt;

            // TODO: This means that allocas without register assigns are possible (lonely, redundant allocas).
            // Register assignment. This includes an instruction.
            if (this->is(TokenKind::OperatorModulo)) {
                OptPtr<RegisterAssign> registerAssign = this->parseRegisterAssign(basicBlock);

                IONIR_PARSER_ASSURE(registerAssign)

                inst = registerAssign->get()->getValue()->dynamicCast<Inst>();

                /**
                 * Register the instruction on the resulting block's symbol
                 * table.
                 */
                symbolTable->insert(registerAssign->get()->getId(), *inst);

                /**
                 * Add the register to the block's registers to be processed later
                 * for code-gen.
                 */
                registers.push_back(*registerAssign);
            }
            // Otherwise, it must be just an instruction.
            else {
                inst = this->parseInst(basicBlock);
            }

            IONIR_PARSER_ASSURE(inst)

            insts.push_back(*inst);
        }

        this->stream.skip();
        basicBlock->setRegisters(registers);
        basicBlock->setInsts(insts);

        return basicBlock;
    }

    OptPtr<FunctionBody> Parser::parseFunctionBody(Ptr<Function> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        Ptr<FunctionBody> functionBody = std::make_shared<FunctionBody>(parent);
        PtrSymbolTable<BasicBlock> basicBlocks = std::make_shared<SymbolTable<Ptr<BasicBlock>>>();

        while (!this->is(TokenKind::SymbolBraceR)) {
            OptPtr<BasicBlock> basicBlock = this->parseBasicBlock(functionBody);

            IONIR_PARSER_ASSURE(basicBlock)

            basicBlocks->insert(basicBlock->get()->getId(), *basicBlock);
        }

        functionBody->setSymbolTable(basicBlocks);

        // Skip over right brace token.
        this->stream.skip();

        return functionBody;
    }

    OptPtr<Module> Parser::parseModule() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordModule))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        PtrSymbolTable<Construct> symbolTable = std::make_shared<SymbolTable<Ptr<Construct>>>();
        Ptr<Module> module = std::make_shared<Module>(*id, symbolTable);

        while (!this->is(TokenKind::SymbolBraceR)) {
            OptPtr<Construct> topLevelConstruct = this->parseTopLevel(module);

            // TODO: Make notice if it has no value? Or is it enough with the notice under 'parseTopLevel()'?
            if (Util::hasValue(topLevelConstruct)) {
                std::optional<std::string> name = Util::getConstructId(*topLevelConstruct);

                if (!name.has_value()) {
                    throw std::runtime_error("Unexpected construct name to be null");
                }

                // TODO: Ensure we're not re-defining something, issue a notice otherwise.
                symbolTable->insert(*name, *topLevelConstruct);
            }

            // No more tokens to process.
            if (!this->stream.hasNext() && !this->is(TokenKind::SymbolBraceR)) {
                return this->makeNotice("Unexpected end of input");
            }
        }

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceR))

        return module;
    }

    OptPtr<RegisterAssign> Parser::parseRegisterAssign(Ptr<BasicBlock> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::OperatorModulo))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolEqual))

        OptPtr<Inst> inst = this->parseInst(parent);

        IONIR_PARSER_ASSURE(inst)

        return std::make_shared<RegisterAssign>(*id, *inst);
    }

    std::optional<std::string> Parser::parseLine() {
        // TODO: Lexer cannot ignore whitespace.
        return "";
    }

    std::optional<Directive> Parser::parseDirective() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolHash))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        std::optional<std::string> content = this->parseLine();

        return std::make_pair(*id, content);
    }
}
