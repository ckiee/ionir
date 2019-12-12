#include <climits>
#include <utility>
#include <vector>
#include <exception>
#include "ast_nodes/binary_expr.h"
#include "ast_nodes/section_kind.h"
#include "misc/util.h"
#include "misc/constants.h"
#include "parser.h"

namespace ionir
{
// TODO: Consider moving to Util class.
bool Parser::withinRange(long value, long from, long to)
{
    return value >= from && value <= to;
}

bool Parser::is(TokenType type)
{
    return this->stream->get().getType() == type;
}

void Parser::expect(TokenType type)
{
    if (!this->is(type))
    {
        throw std::runtime_error("Unexpected token type");
    }
}

void Parser::skipOver(TokenType type)
{
    this->expect(type);
    this->stream->skip();
}

NoticeContext Parser::createNoticeContext()
{
    // TODO
    return NoticeContext("file.ex", 0, 0);
}

Notice Parser::createNotice(NoticeType type, std::string message)
{
    return Notice(this->createNoticeContext(), type, message);
}

std::shared_ptr<Scope> Parser::createScope()
{
    // TODO
    return nullptr;
}

void Parser::pushNotice(NoticeType type, std::string message)
{
    this->notices.push_back(this->createNotice(type, message));
}

Parser::Parser(TokenStream *stream)
    : stream(stream), tokenIdentifier()
{
    //
}

std::vector<Notice> Parser::getNotices() const
{
    return this->notices;
}

std::shared_ptr<Node> Parser::parseTopLevel()
{
    switch (this->stream->get().getType())
    {
    case TokenType::KeywordFunction:
    {
        return this->parseFunction();
    }

    case TokenType::KeywordGlobal:
    {
        return this->parseGlobalVar();
    }

    case TokenType::KeywordExtern:
    {
        return this->parseExtern();
    }

    default:
    {
        throw std::runtime_error("Unknown top-level entity");
    }
    }
}

std::shared_ptr<IntValue> Parser::parseInt()
{
    this->expect(TokenType::LiteralInt);

    // Abstract the token's value to be used in the string -> long conversion.
    std::string tokenValue = this->stream->get().getValue();

    // Attempt to convert token's value to a long.
    long value = std::stol(tokenValue);

    std::optional<IntegerKind> kind = std::nullopt;

    if (this->withinRange(value, SHRT_MIN, SHRT_MAX))
    {
        kind = IntegerKind::Int16;
    }
    else if (this->withinRange(value, INT_MIN, INT_MAX))
    {
        kind = IntegerKind::Int32;
    }
    else if (this->withinRange(value, LONG_MIN, LONG_MAX))
    {
        kind = IntegerKind::Int64;
    }
    // TODO: Missing Int128.
    else
    {
        throw std::runtime_error("Unable to identify integer kind for value");
    }

    // At this point, kind must be set.
    if (!kind.has_value())
    {
        throw std::runtime_error("Expected kind to be defined");
    }

    // Create the integer instance.
    std::shared_ptr<IntValue> integer = std::make_shared<IntValue>(*kind, value);

    // Skip current token.
    this->stream->tryNext();

    // Finally, return the result.
    return integer;
}

std::shared_ptr<CharValue> Parser::parseChar()
{
    this->expect(TokenType::LiteralCharacter);

    // Extract the value from the character token.
    std::string stringValue = this->stream->get().getValue();

    // Skip over character token.
    this->stream->skip();

    // Ensure extracted value only contains a single character.
    if (stringValue.length() > 1)
    {
        throw std::runtime_error("Expected character value length to be 1 character");
    }

    // Create the character construct with the first and only character of the captured value.
    return std::make_shared<CharValue>(stringValue[0]);
}

std::shared_ptr<StringValue> Parser::parseString()
{
    this->expect(TokenType::LiteralString);

    // Extract the value from the string token.
    std::string value = this->stream->get().getValue();

    // Skip over string token.
    this->stream->skip();

    return std::make_shared<StringValue>(value);
}

std::string Parser::parseId()
{
    Token id = this->stream->get();

    this->expect(TokenType::Identifier);

    // Skip over identifier token.
    this->stream->tryNext();

    // Return the identifier's value.
    return id.getValue();
}

std::shared_ptr<Type> Parser::parseType()
{
    std::string id = this->parseId();
    bool isPointer = false;

    // Retrieve the current token.
    Token token = this->stream->get();

    // Type is a pointer.
    if (token.getType() == TokenType::SymbolStar)
    {
        isPointer = true;

        // Skip onto and from star token.
        this->stream->skip(2);
    }

    // Create and return the resulting type construct.
    return std::make_shared<Type>(id, isPointer);
}

Arg Parser::parseArg()
{
    std::shared_ptr<Type> type = this->parseType();
    std::string id = this->parseId();

    return std::make_pair(type, id);
}

std::shared_ptr<Args> Parser::parseArgs()
{
    std::vector<Arg> args = {};
    bool isInfinite = false;

    do
    {
        // Skip comma token if applicable.
        if (this->is(TokenType::SymbolComma))
        {
            // Prevent leading, lonely comma.
            if (args.size() == 0)
            {
                // TODO: Add as notice.
                // this->pushNotice(NoticeType::Error, "Leading comma in argument list is not allowed");
                throw std::runtime_error("Leading comma in argument list is not allowed");
            }

            // Skip over comma token.
            this->stream->next();
        }

        // Parse arg and push onto the vector.
        args.push_back(this->parseArg());
    } while (this->is(TokenType::SymbolComma));

    return std::make_shared<Args>(args, isInfinite);
}

std::shared_ptr<Prototype> Parser::parsePrototype()
{
    std::string id = this->parseId();

    this->skipOver(TokenType::SymbolParenthesesL);

    std::shared_ptr<Args> args = std::make_shared<Args>();

    // Parse arguments if applicable.
    if (!this->is(TokenType::SymbolParenthesesR))
    {
        args = this->parseArgs();
    }

    this->stream->skip();
    this->skipOver(TokenType::SymbolArrow);

    std::shared_ptr<Type> returnType = this->parseType();

    return std::make_shared<Prototype>(id, args, returnType);
}

std::shared_ptr<Extern> Parser::parseExtern()
{
    this->skipOver(TokenType::KeywordExtern);

    std::shared_ptr<Prototype> prototype = this->parsePrototype();

    return std::make_shared<Extern>(prototype);
}

std::shared_ptr<Function> Parser::parseFunction()
{
    this->skipOver(TokenType::KeywordFunction);

    std::shared_ptr<Prototype> prototype = this->parsePrototype();
    std::shared_ptr<Block> body = this->parseBlock();

    return std::make_shared<Function>(prototype, body);
}

std::shared_ptr<GlobalVar> Parser::parseGlobalVar()
{
    this->skipOver(TokenType::KeywordGlobal);

    // TODO

    return nullptr;
}

std::shared_ptr<Value> Parser::parseValue()
{
    Token token = this->stream->get();

    switch (token.getType())
    {
    case TokenType::LiteralInt:
    {
        return this->parseInt();
    }

    case TokenType::LiteralCharacter:
    {
        return this->parseChar();
    }

        // TODO: Missing values.

    default:
    {
        throw std::runtime_error("Expected valid value token");
    }
    }
}

std::optional<std::shared_ptr<Node>> Parser::parsePrimaryExpr()
{
    switch (this->stream->get().getType())
    {
    // Parentheses expression.
    case TokenType::SymbolParenthesesL:
    {
        // TODO
        return nullptr;
    }

    // At this point, return null.
    default:
    {
        return std::nullopt;
    }
    }
}

std::shared_ptr<Node> Parser::parseBinaryExprRightSide(std::shared_ptr<Node> leftSide, int minimalPrecedence)
{
    // If this is a binary operation, find it's precedence.
    while (true)
    {
        // Capture the current token.
        TokenType type = this->stream->get().getType();

        // Calculate precedence for the current token.
        int firstPrecedence = Const::operatorPrecedence[type];

        /**
         * If this is a binary operation that binds at least as tightly
         * as the current binary operation, consume it. Otherwise, the process
         * is complete.
         */
        if (firstPrecedence < minimalPrecedence)
        {
            // TODO: This should throw error? Research.
            return leftSide;
        }

        // At this point, it's a binary operation.
        TokenType binaryOperator = type;

        // TODO: Should check if it's a BINARY operator, not just an operator.
        // Ensure the captured operator is validated.
        if (!TokenIdentifier::isOperator(binaryOperator))
        {
            throw std::runtime_error("Expected token to be a binary operator");
        }

        // Skip operator.
        this->stream->skip();

        // Parse the right-side.
        std::optional<std::shared_ptr<Node>> rightSide = this->parsePrimaryExpr();

        // Ensure that the right-side was successfully parsed.
        if (!rightSide.has_value())
        {
            throw std::runtime_error("Unable to parse the right-side of the binary expression");
        }

        // Determine the token precedence of the current token.
        int secondPrecedence = Const::operatorPrecedence[type];

        /**
         * If binary operator binds less tightly with the right-side than
         * the operator after right-side, let the pending operator take the
         * right-side as its left-side.
         */
        if (firstPrecedence < secondPrecedence)
        {
            // Invoke the right-side parser.
            rightSide = this->parseBinaryExprRightSide(*rightSide, firstPrecedence + 1);

            // Ensure the right-side was successfully parsed.
            if (rightSide == nullptr)
            {
                throw std::runtime_error("Unable to parse the right-side of the binary expression");
            }
        }

        BinaryExprOpts opts = BinaryExprOpts{
            binaryOperator,
            firstPrecedence,
            leftSide,
            rightSide,
        };

        // Create the binary expression entity.
        std::shared_ptr<BinaryExpr> binaryExpr = std::make_shared<BinaryExpr>(opts);

        // TODO: Set the binaryExpr's name during codegen pass.
        // binaryExpr.SetName("tmp");

        // Merge left-side/right-side.
        leftSide = binaryExpr;
    }
}

std::shared_ptr<Section> Parser::parseSection()
{
    this->skipOver(TokenType::SymbolAt);

    std::string id = this->parseId();

    this->skipOver(TokenType::SymbolColon);

    std::vector<std::shared_ptr<Inst>> insts = {};

    while (!this->is(TokenType::SymbolBraceR) && !this->is(TokenType::SymbolAt))
    {
        insts.push_back(this->parseInst());
    }

    this->stream->skip();

    SectionKind kind = SectionKind::Label;

    if (id == Const::sectionInternalPrefix + Const::sectionEntryId)
    {
        kind = SectionKind::Entry;
    }

    else if (Util::stringStartsWith(id, Const::sectionInternalPrefix))
    {
        kind = SectionKind::Internal;
    }

    return std::make_shared<Section>(kind, id, insts);
}

std::shared_ptr<Block> Parser::parseBlock()
{
    this->skipOver(TokenType::SymbolBraceL);

    std::vector<std::shared_ptr<Section>> sections = {};

    while (!this->is(TokenType::SymbolBraceR))
    {
        sections.push_back(this->parseSection());
    }

    // Skip over right brace token.
    this->stream->skip();

    return std::make_shared<Block>(sections);
}

std::shared_ptr<AllocaInst> Parser::parseAllocaInst()
{
    std::shared_ptr<Value> identifierValue = this->parseValue();

    if (identifierValue->getValueKind() != ValueKind::String)
    {
        throw std::runtime_error("The alloca instruction's resulting identifier must be a string value");
    }

    std::string id = identifierValue->dynamicCast<StringValue>()->getValue();
    std::shared_ptr<Type> type = this->parseType();

    return std::make_shared<AllocaInst>(id, type);
}

std::shared_ptr<ReturnInst> Parser::parseReturnInst()
{
    // TODO: Return inst does not necessarily take a value. Instead, it should be allowed to return without value, signaling void.
    std::shared_ptr<Value> value = this->parseValue();

    return std::make_shared<ReturnInst>(value);
}

std::shared_ptr<BranchInst> Parser::parseBranchInst()
{
    std::optional<std::shared_ptr<Node>> condition = this->parsePrimaryExpr();

    // Condition must be set.
    if (!condition.has_value())
    {
        throw std::runtime_error("Expected branch instruction to have a condition");
    }

    // TODO: Use targets.

    std::shared_ptr<Section> body = this->parseSection();
    std::optional<std::shared_ptr<Section>> otherwise = std::nullopt;

    // Parse the otherwise block if applicable.
    if (this->is(TokenType::KeywordElse))
    {
        // Skip over the else keyword.
        this->stream->skip();

        // Parse the otherwise block.
        otherwise = this->parseSection();
    }

    return std::make_shared<BranchInst>(body, *otherwise);
}

std::shared_ptr<GotoInst> Parser::parseGotoInst()
{
    std::string target = this->parseId();
    std::shared_ptr<GotoInst> gotoInst = std::make_shared<GotoInst>(this->createNotice, target);

    // TODO: createScope has not been defined yet.
    return gotoInst;
}

std::shared_ptr<Inst> Parser::parseInst()
{
    // Parse the instruction's name to determine which argument parser to invoke.
    std::string id = this->parseId();

    std::shared_ptr<Inst> inst;

    // TODO: Hard-coded strings. Should be mapped into InstKind enum.
    if (id == "alloca")
    {
        return this->parseAllocaInst();
    }
    else if (id == "return")
    {
        return this->parseReturnInst();
    }
    else if (id == "goto")
    {
        return this->parseGotoInst();
    }
    else
    {
        throw std::runtime_error("Unrecognized instruction name");
    }
}
} // namespace ionir
