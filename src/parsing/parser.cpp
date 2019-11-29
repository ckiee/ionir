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
    return this->stream.get().getType() == type;
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
    this->stream.skip();
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

void Parser::pushNotice(NoticeType type, std::string message)
{
    this->notices.push_back(this->createNotice(type, message));
}

Parser::Parser(TokenStream stream) : stream(stream)
{
    //
}

std::vector<Notice> Parser::getNotices() const
{
    return this->notices;
}

IntValue *Parser::parseInt()
{
    this->expect(TokenType::LiteralInt);

    // Abstract the token's value to be used in the string -> long conversion.
    std::string tokenValue = this->stream.get().getValue();

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
    IntValue *integer = new IntValue(*kind, value);

    // Skip current token.
    this->stream.tryNext();

    // Finally, return the result.
    return integer;
}

CharValue *Parser::parseChar()
{
    this->expect(TokenType::LiteralCharacter);

    // Extract the value from the character token.
    std::string stringValue = this->stream.get().getValue();

    // Skip over character token.
    this->stream.skip();

    // Ensure extracted value only contains a single character.
    if (stringValue.length() > 1)
    {
        throw std::runtime_error("Expected character value length to be 1 character");
    }

    // Create the character construct with the first and only character of the captured value.
    return new CharValue(stringValue[0]);
}

StringValue *Parser::parseString()
{
    this->expect(TokenType::LiteralString);

    // Extract the value from the string token.
    std::string value = this->stream.get().getValue();

    // Skip over string token.
    this->stream.skip();

    return new StringValue(value);
}

std::string Parser::parseIdentifier()
{
    Token identifier = this->stream.get();

    this->expect(TokenType::Identifier);

    // Skip over identifier token.
    this->stream.tryNext();

    // Return the identifier's value.
    return identifier.getValue();
}

Type *Parser::parseType()
{
    std::string identifier = this->parseIdentifier();

    bool isPointer = false;

    // Retrieve the current token.
    Token token = this->stream.get();

    // Type is a pointer.
    if (token.getType() == TokenType::SymbolStar)
    {
        isPointer = true;

        // Skip onto and from star token.
        this->stream.skip(2);
    }

    // Create and return the resulting type construct.
    return new Type(identifier, isPointer);
}

Arg Parser::parseArg()
{
    Type *type = this->parseType();
    std::string identifier = this->parseIdentifier();

    return std::make_pair(type, identifier);
}

Args Parser::parseArgs()
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
            this->stream.next();
        }

        // Parse arg and push onto the vector.
        args.push_back(this->parseArg());
    } while (this->is(TokenType::SymbolComma));

    return Args(args, isInfinite);
}

Prototype *Parser::parsePrototype()
{
    Type *returnType = this->parseType();
    std::string identifier = this->parseIdentifier();

    this->skipOver(TokenType::SymbolParenthesesL);

    Args args = Args({}, false);

    // Parse arguments if applicable.
    if (!this->is(TokenType::SymbolParenthesesR))
    {
        args = this->parseArgs();
    }

    this->skipOver(TokenType::SymbolParenthesesR);

    return new Prototype(identifier, args, returnType);
}

Extern *Parser::parseExtern()
{
    this->skipOver(TokenType::KeywordExtern);

    Prototype *prototype = this->parsePrototype();
    Extern *externNode = new Extern(prototype);

    return externNode;
}

Value *Parser::parseValue()
{
    Token token = this->stream.get();

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

std::optional<Node *> Parser::parsePrimaryExpr()
{
    switch (this->stream.get().getType())
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

Node *Parser::parseBinaryExprRightSide(Node *leftSide, int minimalPrecedence)
{
    // If this is a binary operation, find it's precedence.
    while (true)
    {
        // Capture the current token.
        Token token = this->stream.get();

        // Calculate precedence for the current token.
        int firstPrecedence = Precedence.Get(token);

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
        TokenType binaryOperator = token.getType();

        // TODO: Should check if it's a BINARY operator, not just an operator.
        // Ensure the captured operator is validated.
        if (!TokenIdentifier.IsOperator(binaryOperator))
        {
            throw std::runtime_error("Expected token to be a binary operator");
        }

        // Skip operator.
        this->stream.skip();

        // Parse the right-side.
        std::optional<Node *> rightSide = this->parsePrimaryExpr();

        // Ensure that the right-side was successfully parsed.
        if (!rightSide.has_value())
        {
            throw std::runtime_error("Unable to parse the right-side of the binary expression");
        }

        // Determine the token precedence of the current token.
        int secondPrecedence = Precedence.Get(token);

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

        // Create the binary expression entity.
        BinaryExpr *binaryExpr = new BinaryExpr(binaryOperator, leftSide, *rightSide, firstPrecedence);

        // TODO: Name is temporary?
        // Set the name of the binary expression's output.
        binaryExpr.SetName("tmp");

        // Merge left-side/right-side.
        leftSide = binaryExpr;
    }
}

AllocaInst *Parser::parseAllocaInst()
{
    Value *identifierValue = this->parseValue();

    if (identifierValue->getValueKind() != ValueKind::String)
    {
        throw std::runtime_error("The alloca instruction's resulting identifier must be a string value");
    }

    std::string identifier = ((StringValue *)identifierValue)->getValue();
    Type *type = this->parseType();

    return new AllocaInst(identifier, type);
}

ReturnInst *Parser::parseReturnInst()
{
    // TODO: Return inst does not necessarily take a value. Instead, it should be allowed to return without value, signaling void.
    Value *value = this->parseValue();

    return new ReturnInst(value);
}

BranchInst *Parser::parseBranchInst()
{
    std::optional<Node *> condition = this->parsePrimaryExpr();

    // Condition must be set.
    if (!condition.has_value())
    {
        throw std::runtime_error("Expected branch instruction to have a condition");
    }

    Block *body = this->parseBlock();
    std::optional<Block *> otherwise = std::nullopt;

    // Parse the otherwise block if applicable.
    if (this->is(TokenType::KeywordElse))
    {
        // Skip over the else keyword.
        this->stream.skip();

        // Parse the otherwise block.
        otherwise = this->parseBlock();
    }

    return new BranchInst(body, *otherwise);
}

PartialInst *Parser::parseInst()
{
    // Parse the instruction's name to determine which argument parser to invoke.
    std::string identifier = this->parseIdentifier();

    // TODO: Hard-coded strings. Should be mapped into InstKind enum.
    if (identifier == "alloca")
    {
        return this->parseAllocaInst();
    }
    else if (identifier == "return")
    {
        return this->parseReturnInst();
    }
    else if (identifier == "goto")
    {
        // TODO
    }
    else
    {
        throw std::runtime_error("Unrecognized instruction name");
    }
}

Section *Parser::parseSection()
{
    std::string identifier = this->parseIdentifier();

    this->skipOver(TokenType::SymbolColon);
    this->skipOver(TokenType::SymbolBraceL);

    std::vector<PartialInst *> insts = {};

    while (!this->is(TokenType::SymbolBraceR))
    {
        insts.push_back(this->parseInst());
    }

    this->skipOver(TokenType::SymbolBraceR);

    SectionKind kind = SectionKind::Label;

    if (identifier == Constants::sectionInternalPrefix + Constants::sectionEntryIdentifier)
    {
        kind = SectionKind::Entry;
    }

    else if (Util::stringStartsWith(identifier, Constants::sectionInternalPrefix))
    {
        kind = SectionKind::Internal;
    }

    return new Section(kind, identifier, insts);
}

Block *Parser::parseBlock()
{
    this->skipOver(TokenType::SymbolBraceL);

    std::vector<Section *> sections = {};

    while (this->is(TokenType::SymbolBraceR))
    {
        sections.push_back(this->parseSection());
    }

    // Skip over right brace token.
    this->stream.skip();

    return new Block(sections);
}

GotoInst *Parser::parseGotoInst()
{
    // TODO

    return nullptr;
}
} // namespace ionir
