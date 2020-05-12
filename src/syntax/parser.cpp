#include <vector>
#include <ionir/construct/expr.h>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
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

    OptPtr<Construct> Parser::parseTopLevel() {
        switch (this->stream.get().getKind()) {
            case TokenKind::KeywordModule: {
                return this->parseModule();
            }

            case TokenKind::KeywordFunction: {
                return this->parseFunction();
            }

            case TokenKind::KeywordGlobal: {
                return this->parseGlobal();
            }

            case TokenKind::KeywordExtern: {
                return this->parseExtern();
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

    OptPtr<Section> Parser::parseSection(Ptr<Block> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolAt))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolColon))
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        // Determine the section's kind.
        SectionKind kind = SectionKind::Label;

        // TODO: Id cannot possibly start with the internal prefix since parseId() does not support '.' on an id!

        if (*id == Const::sectionEntryId) {
            kind = SectionKind::Entry;
        }
        else if (Util::stringStartsWith(*id, Const::sectionInternalPrefix)) {
            kind = SectionKind::Internal;
        }

        Ptr<Section> section = std::make_shared<Section>(SectionOpts{
            parent,
            kind,
            *id
        });

        std::vector<Ptr<Inst>> insts = {};
        PtrSymbolTable<Inst> symbolTable = section->getSymbolTable();

        while (!this->is(TokenKind::SymbolBraceR) && !this->is(TokenKind::SymbolAt)) {
            OptPtr<Inst> inst = this->parseInst(section);

            IONIR_PARSER_ASSURE(inst)

            insts.push_back(*inst);

            /**
             * Register the alloca instruction on
             * the resulting section's symbol table.
             */
            if (inst->get()->getInstKind() == InstKind::Alloca) {
                Ptr<AllocaInst> allocaInst = inst->get()->dynamicCast<AllocaInst>();

                symbolTable->insert(*allocaInst->getYieldId(), allocaInst);
            }
        }

        this->stream.skip();
        section->setInsts(insts);

        return section;
    }

    OptPtr<Block> Parser::parseBlock(Ptr<Function> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        Ptr<Block> block = std::make_shared<Block>(parent);
        PtrSymbolTable<Section> sections = std::make_shared<SymbolTable<Ptr<Section>>>();

        while (!this->is(TokenKind::SymbolBraceR)) {
            OptPtr<Section> section = this->parseSection(block);

            IONIR_PARSER_ASSURE(section)

            sections->insert(section->get()->getId(), *section);
        }

        block->setSymbolTable(sections);

        // Skip over right brace token.
        this->stream.skip();

        return block;
    }

    OptPtr<Module> Parser::parseModule() {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordModule))

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolBraceL))

        PtrSymbolTable<Construct> symbolTable = std::make_shared<SymbolTable<Ptr<Construct>>>();

        while (!this->is(TokenKind::SymbolBraceR)) {
            OptPtr<Construct> topLevelConstruct = this->parseTopLevel();

            // TODO: Make notice if it has no value? Or is it enough with the notice under 'parseTopLevel()'?
            if (topLevelConstruct.has_value()) {
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

        return std::make_shared<Module>(*id, symbolTable);
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
