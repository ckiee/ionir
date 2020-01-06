#include <vector>
#include <ionir/construct/expr.h>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    TokenIdentifier Parser::getTokenIdentifier() const {
        return this->tokenIdentifier;
    }

    bool Parser::is(TokenKind tokenKind) {
        return this->stream.get().getKind() == tokenKind;
    }

    bool Parser::expect(TokenKind tokenKind) {
        if (!this->is(tokenKind)) {
            this->makeNotice("Expected token kind: " + std::to_string((int)tokenKind) + ", but got: " +
                std::to_string((int)this->stream.get().getKind()), NoticeType::Fatal);

            return false;
        }

        return true;
    }

    void Parser::skipOver(TokenKind tokenKind) {
        this->expect(tokenKind);
        this->stream.skip();
    }

    NoticeFactory Parser::createNoticeFactory() {
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
        : stream(stream), stackTrace(stackTrace), filePath(filePath), tokenIdentifier() {
        //
    }

    StackTrace Parser::getStackTrace() const {
        return this->stackTrace;
    }

    std::string Parser::getFilePath() const {
        return this->filePath;
    }

    std::optional<Ptr<Construct>> Parser::parseTopLevel() {
        switch (this->stream.get().getKind()) {
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

    std::optional<Ptr<Type>> Parser::parseType() {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        bool isPointer = false;

        // Retrieve the current token.
        Token token = this->stream.get();

        // Type is a pointer.
        if (token.getKind() == TokenKind::SymbolStar) {
            isPointer = true;

            // Skip onto and from star token.
            this->stream.skip(2);
        }

        // Create and return the resulting type construct.
        return std::make_shared<Type>(*id, Util::resolveTypeKind(*id), isPointer);
    }

    std::optional<Ptr<Type>> Parser::parseTypePrefix() {
        this->skipOver(TokenKind::SymbolBracketL);

        std::optional<Ptr < Type>>
        type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        this->skipOver(TokenKind::SymbolBracketR);

        return type;
    }

    std::optional<Ptr<Global>> Parser::parseGlobal() {
        this->skipOver(TokenKind::KeywordGlobal);

        // TODO

        return std::nullopt;
    }

    std::optional<Ptr<Section>> Parser::parseSection(Ptr<Block> parent) {
        this->skipOver(TokenKind::SymbolAt);

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        this->skipOver(TokenKind::SymbolColon);
        this->skipOver(TokenKind::SymbolBraceL);

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

        while (!this->is(TokenKind::SymbolBraceR) && !this->is(TokenKind::SymbolAt)) {
            std::optional<Ptr<Inst>> inst = this->parseInst(section);

            IONIR_PARSER_ASSURE(inst)

            insts.push_back(*inst);
        }

        this->stream.skip();
        section->setInsts(insts);

        return section;
    }

    std::optional<Ptr<Block>> Parser::parseBlock(Ptr<Function> parent) {
        this->skipOver(TokenKind::SymbolBraceL);

        Ptr<Block> block = std::make_shared<Block>(parent);
        std::vector<Ptr<Section>> sections = {};

        while (!this->is(TokenKind::SymbolBraceR)) {
            std::optional<Ptr<Section>> section = this->parseSection(block);

            IONIR_PARSER_ASSURE(section)

            sections.push_back(*section);
        }

        block->setSections(sections);

        // Skip over right brace token.
        this->stream.skip();

        return block;
    }
}
