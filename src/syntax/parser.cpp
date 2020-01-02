#include <climits>
#include <utility>
#include <vector>
#include <ionir/construct/expr/expr.h>
#include <ionir/construct/expr/binary_expr.h>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>

#define IONIR_PARSER_EXPECT(type) if (!this->expect(type)) { return std::nullopt; }
#define IONIR_PARSER_ASSURE(value) if (!value.has_value()) { return this->makeNotice("Unexpected parsed constructed to be null"); }

namespace ionir {
    TokenIdentifier Parser::getTokenIdentifier() const {
        return this->tokenIdentifier;
    }

    bool Parser::is(TokenKind tokenKind) {
        return this->stream->get().getKind() == tokenKind;
    }

    bool Parser::expect(TokenKind tokenKind) {
        if (!this->is(tokenKind)) {
            this->makeNotice("Expected token kind: " + std::to_string((int)tokenKind) + ", but got: " +
                std::to_string((int)this->stream->get().getKind()), NoticeType::Fatal);

            return false;
        }

        return true;
    }

    void Parser::skipOver(TokenKind tokenKind) {
        this->expect(tokenKind);
        this->stream->skip();
    }

    NoticeFactory Parser::createNoticeFactory() {
        // Abstract current Token for easier access.
        Token token = this->stream->get();

        return NoticeFactory(NoticeContext{
            this->filePath,
            token.getLineNumber(),
            token.getStartPosition()
        });
    }

    std::nullopt_t Parser::makeNotice(std::string message, NoticeType type = NoticeType::Error) {
        this->stackTrace.push_back(this->createNoticeFactory().make(type, message));

        return std::nullopt;
    }

    Parser::Parser(TokenStream *stream, StackTrace stackTrace, std::string filePath)
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
        switch (this->stream->get().getKind()) {
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

    std::optional<Ptr<IntegerValue>> Parser::parseInt() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralInt);

        // Abstract the token's value to be used in the string -> long conversion.
        std::string tokenValue = this->stream->get().getValue();

        // Attempt to convert token's value to a long.
        long value = std::stol(tokenValue);

        std::optional<IntegerKind> kind = std::nullopt;

        if (Util::withinRange(value, SHRT_MIN, SHRT_MAX)) {
            kind = IntegerKind::Int16;
        }
        else if (Util::withinRange(value, INT_MIN, INT_MAX)) {
            kind = IntegerKind::Int32;
        }
        else if (Util::withinRange(value, LONG_MIN, LONG_MAX)) {
            kind = IntegerKind::Int64;
        }
            // TODO: Missing Int128.
        else {
            return this->makeNotice("Unable to identify integer kind for value");
        }

        // At this point, kind must be set.
        if (!kind.has_value()) {
            return this->makeNotice("Expected kind to be defined");
        }

        // Create the integer instance.
        Ptr<IntegerValue> integer = std::make_shared<IntegerValue>(*kind, value);

        // Skip current token.
        this->stream->tryNext();

        // Finally, return the result.
        return integer;
    }

    std::optional<Ptr<CharValue>> Parser::parseChar() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralCharacter);

        // Extract the value from the character token.
        std::string stringValue = this->stream->get().getValue();

        // Skip over character token.
        this->stream->skip();

        // Ensure extracted value only contains a single character.
        if (stringValue.length() > 1) {
            return this->makeNotice("Character value length must be at most 1 character");
        }

        // Create the character construct with the first and only character of the captured value.
        return std::make_shared<CharValue>(stringValue[0]);
    }

    std::optional<Ptr<StringValue>> Parser::parseString() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralString);

        // Extract the value from the string token.
        std::string value = this->stream->get().getValue();

        // Skip over string token.
        this->stream->skip();

        return std::make_shared<StringValue>(value);
    }

    std::optional<std::string> Parser::parseId() {
        Token id = this->stream->get();

        IONIR_PARSER_EXPECT(TokenKind::Identifier)

        // Skip over identifier token.
        this->stream->skip();

        // Return the identifier's value.
        return id.getValue();
    }

    std::optional<Ptr<Type>> Parser::parseType() {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        bool isPointer = false;

        // Retrieve the current token.
        Token token = this->stream->get();

        // Type is a pointer.
        if (token.getKind() == TokenKind::SymbolStar) {
            isPointer = true;

            // Skip onto and from star token.
            this->stream->skip(2);
        }

        // Create and return the resulting type construct.
        return std::make_shared<Type>(*id, isPointer);
    }

    std::optional<Arg> Parser::parseArg() {
        std::optional<Ptr<Type>> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        return std::make_pair(*type, *id);
    }

    std::optional<Ptr<Args>> Parser::parseArgs() {
        std::vector<Arg> args = {};
        bool isInfinite = false;

        do {
            // Skip comma token if applicable.
            if (this->is(TokenKind::SymbolComma)) {
                // Prevent leading, lonely comma.
                if (args.size() == 0) {
                    return this->makeNotice("Leading comma in argument list is not allowed");
                }

                // Skip over comma token.
                this->stream->next();
            }

            std::optional<Arg> arg = this->parseArg();

            IONIR_PARSER_ASSURE(arg)

            // Parse arg and push onto the vector.
            args.push_back(*arg);
        } while (this->is(TokenKind::SymbolComma));

        return std::make_shared<Args>(args, isInfinite);
    }

    std::optional<Ptr<Prototype>> Parser::parsePrototype() {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        this->skipOver(TokenKind::SymbolParenthesesL);

        Ptr<Args> args = std::make_shared<Args>();

        // Parse arguments if applicable.
        if (!this->is(TokenKind::SymbolParenthesesR)) {
            std::optional<Ptr<Args>> temporaryArgs = this->parseArgs();

            IONIR_PARSER_ASSURE(temporaryArgs)

            args = *temporaryArgs;
        }

        this->stream->skip();
        this->skipOver(TokenKind::SymbolArrow);

        std::optional<Ptr<Type>> returnType = this->parseType();

        IONIR_PARSER_ASSURE(returnType)

        return std::make_shared<Prototype>(*id, args, *returnType);
    }

    std::optional<Ptr<Extern>> Parser::parseExtern() {
        this->skipOver(TokenKind::KeywordExtern);

        std::optional<Ptr<Prototype>> prototype = this->parsePrototype();

        IONIR_PARSER_ASSURE(prototype)

        return std::make_shared<Extern>(*prototype);
    }

    std::optional<Ptr<Function>> Parser::parseFunction() {
        this->skipOver(TokenKind::KeywordFunction);

        std::optional<Ptr<Prototype>> prototype = this->parsePrototype();
        std::optional<Ptr<Block>> body = this->parseBlock(nullptr);

        IONIR_PARSER_ASSURE(prototype)
        IONIR_PARSER_ASSURE(body)

        Ptr<Function> function = std::make_shared<Function>(*prototype, *body);

        body->get()->setParent(function);

        return function;
    }

    std::optional<Ptr<Global>> Parser::parseGlobal() {
        this->skipOver(TokenKind::KeywordGlobal);

        // TODO

        return std::nullopt;
    }

    std::optional<Ptr<Value>> Parser::parseValue() {
        Token token = this->stream->get();

        switch (token.getKind()) {
            case TokenKind::LiteralInt: {
                return this->parseInt();
            }

            case TokenKind::LiteralCharacter: {
                return this->parseChar();
            }

                // TODO: Missing values.

            default: {
                return this->makeNotice("Expected valid value token");
            }
        }
    }

    std::optional<Ptr<IdExpr>> Parser::parseIdExpr() {
        // TODO

        return std::nullopt;
    }

    std::optional<Ptr<Expr>> Parser::parsePrimaryExpr() {
        TokenKind tokenKind = this->stream->get().getKind();

        return this->makeNotice("Not yet implemented");

        switch (tokenKind) {
            // Identifier expression.
            case TokenKind::Identifier: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

                // TODO: Handle other TokenTypes.
        }

        // At this point, nothing was found.
        return std::nullopt;
    }

    std::optional<Ptr<Expr>> Parser::parseBinaryExprRightSide(Ptr<Expr> leftSide, int minimalPrecedence) {
        // If this is a binary operation, find it's precedence.
        while (true) {
            // Capture the current token.
            TokenKind tokenKind = this->stream->get().getKind();

            // Calculate precedence for the current token.
            int firstPrecedence = Const::operatorPrecedence[tokenKind];

            /**
             * If this is a binary operation that binds at least as tightly
             * as the current binary operation, consume it. Otherwise, the process
             * is complete.
             */
            if (firstPrecedence < minimalPrecedence) {
                // TODO: This should throw error? Research.
                return leftSide;
            }

            // At this point, it's a binary operation.
            TokenKind binaryOperatorKind = tokenKind;

            // TODO: Should check if it's a BINARY operator, not just an operator.
            // Ensure the captured operator is validated.
            if (!TokenIdentifier::isOperator(binaryOperatorKind)) {
                return this->makeNotice("Expected token to be a binary operator");
            }

            // Skip operator.
            this->stream->skip();

            // Parse the right-side.
            std::optional<Ptr<Expr>> rightSide = this->parsePrimaryExpr();

            IONIR_PARSER_ASSURE(rightSide)

            // Ensure that the right-side was successfully parsed.
            if (!rightSide.has_value()) {
                return this->makeNotice("Unable to parse the right-side of the binary expression");
            }

            // Determine the token precedence of the current token.
            int secondPrecedence = Const::operatorPrecedence[tokenKind];

            /**
             * If binary operator binds less tightly with the right-side than
             * the operator after right-side, let the pending operator take the
             * right-side as its left-side.
             */
            if (firstPrecedence < secondPrecedence) {
                // Invoke the right-side parser.
                rightSide = this->parseBinaryExprRightSide(*rightSide, firstPrecedence + 1);

                // Ensure the right-side was successfully parsed.
                if (rightSide == nullptr) {
                    return this->makeNotice("Unable to parse the right-side of the binary expression");
                }
            }

            BinaryExprOpts opts = BinaryExprOpts{
                binaryOperatorKind,
                firstPrecedence,
                leftSide,
                rightSide,
            };

            // Create the binary expression entity.
            Ptr<BinaryExpr> binaryExpr = std::make_shared<BinaryExpr>(opts);

            // TODO: Set the binaryExpr's name during codegen pass.
            // binaryExpr.SetName("tmp");

            // Merge left-side/right-side.
            leftSide = binaryExpr;
        }
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

        this->stream->skip();
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
        this->stream->skip();

        return block;
    }

    std::optional<Ptr<AllocaInst>> Parser::parseAllocaInst(Ptr<Section> parent) {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        std::optional<Ptr<Type>> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        return std::make_shared<AllocaInst>(AllocaInstOpts{
            parent,
            *id,
            *type,
        });
    }

    std::optional<Ptr<ReturnInst>> Parser::parseReturnInst(Ptr<Section> parent) {
        // TODO: Return inst does not necessarily take a value. Instead, it should be allowed to return without value, signaling void.
        std::optional<Ptr<Value>> value = this->parseValue();

        IONIR_PARSER_ASSURE(value)

        return std::make_shared<ReturnInst>(ReturnInstOpts{
            parent,
            *value
        });
    }

    std::optional<Ptr<BranchInst>> Parser::parseBranchInst(Ptr<Section> parent) {
        // std::optional<Ptr<Expr>> condition = this->parsePrimaryExpr();

        // // Condition must be set.
        // if (!condition.has_value())
        // {
        //     throw std::runtime_error("Expected branch instruction to have a condition");
        // }

        // // TODO: Use targets.

        // Ptr<Section> body = this->parseSection();
        // std::optional<Ptr<Section>> otherwise = std::nullopt;

        // // Parse the otherwise block if applicable.
        // if (this->is(TokenKind::KeywordElse))
        // {
        //     // Skip over the else keyword.
        //     this->stream->skip();

        //     // Parse the otherwise block.
        //     otherwise = this->parseSection();
        // }

        // return std::make_shared<BranchInst>(BranchInstOpts{
        //     parent,
        //     *condition,
        //     body,
        //     *otherwise,
        // });

        // TODO

        return std::nullopt;
    }

    std::optional<Ptr<CallInst>> Parser::parseCallInst(Ptr<Section> parent) {
        // TODO

        return this->makeNotice("Not yet implemented");
    }

    std::optional<Ptr<Inst>> Parser::parseInst(Ptr<Section> parent) {
        // Parse the instruction's name to determine which argument parser to invoke.
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        std::optional<Ptr<Inst>> inst;

        // TODO: Missing more instructions.

        if (id == ConstName::instAlloca) {
            inst = this->parseAllocaInst(parent);
        }
        else if (id == ConstName::instReturn) {
            inst = this->parseReturnInst(parent);
        }
        else if (id == ConstName::instCall) {
            inst = this->parseCallInst(parent);
        }
        else {
            return this->makeNotice("Unrecognized instruction name");
        }

        // All instructions should end denoted by a semi-colon.
        this->skipOver(TokenKind::SymbolSemiColon);

        return inst;
    }
}
