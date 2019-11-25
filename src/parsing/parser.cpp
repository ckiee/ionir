#include <climits>
#include <utility>
#include <vector>
#include <exception>
#include "parser.h"

namespace ionir
{
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

LiteralInt *Parser::parseInt()
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
    LiteralInt *integer = new LiteralInt(*kind, value);

    // Skip current token.
    this->stream.tryNext();

    // Finally, return the result.
    return integer;
}

LiteralChar *Parser::parseChar()
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
    return new LiteralChar(stringValue[0]);
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
    Value *value = this->parseValue();

    return new ReturnInst(value);
}

Inst *Parser::parseInst()
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
    else
    {
        throw std::runtime_error("Unrecognized instruction name");
    }
}

Block *Parser::parseBlock()
{
    std::string identifier = this->parseIdentifier();

    this->skipOver(TokenType::SymbolColon);
    this->skipOver(TokenType::SymbolBraceL);

    std::vector<Inst *> insts = {};

    while (!this->is(TokenType::SymbolBraceR))
    {
        insts.push_back(this->parseInst());
    }

    this->skipOver(TokenType::SymbolBraceR);

    return new Block(identifier, insts);
}
} // namespace ionir
