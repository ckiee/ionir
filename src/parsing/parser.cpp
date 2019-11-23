#include <exception>
#include "parser.h"

namespace ionir
{
bool Parser::withinRange(long value, long from, long to)
{
    return value >= from && value <= to;
}

void Parser::expect(TokenType type)
{
    if (!this->is(type))
    {
        throw std::runtime_error("Unexpected token type");
    }
}

bool Parser::is(TokenType type)
{
    return this->stream.get().getType() == type;
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

std::vector<Notice> getNotices() const
{
    return this->notices;
}

/**
 * Parses a literal integer in the form of
 * long (or integer 64).
 */
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
    LiteralInt result = LiteralInt(*kind, value);

    // Skip current token.
    this->stream.tryNext();

    // Finally, return the result.
    return &result;
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

Type Parser::parseType()
{
    std::string identifier = this->parseIdentifier();

    bool isPointer = false;

    // Peek at next token.
    std::optional<Token> nextToken = this->stream.peek();

    // Type is a pointer.
    if (nextToken.has_value() && (*nextToken).getType() == TokenType::SymbolStar)
    {
        isPointer = true;

        // Skip onto and from star token.
        this->stream.skip(2);
    }

    // Create and return the resulting type construct.
    return Type(identifier, isPointer);
}

Arg Parser::parseArg()
{
    std::string identifier = this->parseIdentifier();
    Type type = this->parseType();

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

Extern *Parser::parseExtern()
{
    this->expect(TokenType::KeywordExtern);
    this->stream.next();
    this->expect(TokenType::Identifier);

    Token identifier = this->stream.next();

    Prototype prototype = Prototype(identifier.getValue(), nullptr, nullptr, false);

    Extern externNode = Extern();

    // TODO: Finish implementation.
    return nullptr;
}
} // namespace ionir
