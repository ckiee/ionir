#include <climits>
#include <utility>
#include <vector>
#include <exception>
#include "construct/expr/expr.h"
#include "construct/expr/binary_expr.h"
#include "misc/util.h"
#include "const/const.h"
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

Ptr<Scope> Parser::createScope()
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

Ptr<Construct> Parser::parseTopLevel()
{
    switch (this->stream->get().getType())
    {
    case TokenType::KeywordFunction:
    {
        return this->parseFunction();
    }

    case TokenType::KeywordGlobal:
    {
        return this->parseGlobal();
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

Ptr<IntegerValue> Parser::parseInt()
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
    Ptr<IntegerValue> integer = std::make_shared<IntegerValue>(*kind, value);

    // Skip current token.
    this->stream->tryNext();

    // Finally, return the result.
    return integer;
}

Ptr<CharValue> Parser::parseChar()
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

Ptr<StringValue> Parser::parseString()
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

Ptr<Type> Parser::parseType()
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
    Ptr<Type> type = this->parseType();
    std::string id = this->parseId();

    return std::make_pair(type, id);
}

Ptr<Args> Parser::parseArgs()
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

Ptr<Prototype> Parser::parsePrototype()
{
    std::string id = this->parseId();

    this->skipOver(TokenType::SymbolParenthesesL);

    Ptr<Args> args = std::make_shared<Args>();

    // Parse arguments if applicable.
    if (!this->is(TokenType::SymbolParenthesesR))
    {
        args = this->parseArgs();
    }

    this->stream->skip();
    this->skipOver(TokenType::SymbolArrow);

    Ptr<Type> returnType = this->parseType();

    return std::make_shared<Prototype>(id, args, returnType);
}

Ptr<Extern> Parser::parseExtern()
{
    this->skipOver(TokenType::KeywordExtern);

    Ptr<Prototype> prototype = this->parsePrototype();

    return std::make_shared<Extern>(prototype);
}

Ptr<Function> Parser::parseFunction()
{
    this->skipOver(TokenType::KeywordFunction);

    Ptr<Prototype> prototype = this->parsePrototype();
    Ptr<Block> body = this->parseBlock();

    return std::make_shared<Function>(prototype, body);
}

Ptr<Global> Parser::parseGlobal()
{
    this->skipOver(TokenType::KeywordGlobal);

    // TODO

    return nullptr;
}

Ptr<Value> Parser::parseValue()
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

Ptr<IdExpr> Parser::parseIdExpr()
{
    // TODO
}

std::optional<Ptr<Expr>> Parser::parsePrimaryExpr()
{
    TokenType type = this->stream->get().getType();

    switch (type)
    {
    // Identifier expression.
    case TokenType::Identifier:
    {
    }
    }

    // At this point, nothing was found.
    return std::nullopt;
}

Ptr<Expr> Parser::parseBinaryExprRightSide(Ptr<Expr> leftSide, int minimalPrecedence)
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
        std::optional<Ptr<Expr>> rightSide = this->parsePrimaryExpr();

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
        Ptr<BinaryExpr> binaryExpr = std::make_shared<BinaryExpr>(opts);

        // TODO: Set the binaryExpr's name during codegen pass.
        // binaryExpr.SetName("tmp");

        // Merge left-side/right-side.
        leftSide = binaryExpr;
    }
}

Ptr<Section> Parser::parseSection(Ptr<Block> parent)
{
    this->skipOver(TokenType::SymbolAt);

    std::string id = this->parseId();

    this->skipOver(TokenType::SymbolColon);

    // Determine the section's kind.
    SectionKind kind = SectionKind::Label;

    if (id == Const::sectionInternalPrefix + Const::sectionEntryId)
    {
        kind = SectionKind::Entry;
    }
    else if (Util::stringStartsWith(id, Const::sectionInternalPrefix))
    {
        kind = SectionKind::Internal;
    }

    Ptr<Section> section = std::make_shared<Section>(SectionOpts{
        parent,
        kind,
        id,
    });

    std::vector<Ptr<Inst>> insts = {};

    while (!this->is(TokenType::SymbolBraceR) && !this->is(TokenType::SymbolAt))
    {
        insts.push_back(this->parseInst(section));
    }

    this->stream->skip();
    section->setInsts(insts);

    return section;
}

Ptr<Block> Parser::parseBlock()
{
    this->skipOver(TokenType::SymbolBraceL);

    Ptr<Block> block = std::make_shared<Block>();
    std::vector<Ptr<Section>> sections = {};

    while (!this->is(TokenType::SymbolBraceR))
    {
        sections.push_back(this->parseSection(block));
    }

    block->setSections(sections);

    // Skip over right brace token.
    this->stream->skip();

    return block;
}

Ptr<AllocaInst> Parser::parseAllocaInst(Ptr<Section> parent)
{
    std::string id = this->parseId();
    Ptr<Type> type = this->parseType();

    return std::make_shared<AllocaInst>(AllocaInstOpts{
        parent,
        id,
        type,
    });
}

Ptr<ReturnInst> Parser::parseReturnInst(Ptr<Section> parent)
{
    // TODO: Return inst does not necessarily take a value. Instead, it should be allowed to return without value, signaling void.
    Ptr<Value> value = this->parseValue();

    return std::make_shared<ReturnInst>(ReturnInstOpts{
        parent,
        value,
    });
}

Ptr<BranchInst> Parser::parseBranchInst(Ptr<Section> parent)
{
    std::optional<Ptr<Expr>> condition = this->parsePrimaryExpr();

    // Condition must be set.
    if (!condition.has_value())
    {
        throw std::runtime_error("Expected branch instruction to have a condition");
    }

    // TODO: Use targets.

    Ptr<Section> body = this->parseSection();
    std::optional<Ptr<Section>> otherwise = std::nullopt;

    // Parse the otherwise block if applicable.
    if (this->is(TokenType::KeywordElse))
    {
        // Skip over the else keyword.
        this->stream->skip();

        // Parse the otherwise block.
        otherwise = this->parseSection();
    }

    return std::make_shared<BranchInst>(BranchInstOpts{
        parent,
        *condition,
        body,
        *otherwise,
    });
}

Ptr<CallInst> Parser::parseCallInst(Ptr<Section> parent)
{
    // TODO

    return nullptr;
}

Ptr<Inst> Parser::parseInst(Ptr<Section> parent)
{
    // Parse the instruction's name to determine which argument parser to invoke.
    std::string id = this->parseId();

    Ptr<Inst> inst;

    // TODO: Missing more instructions.

    // TODO: Hard-coded strings. Should be mapped into InstKind enum.
    if (id == "alloca")
    {
        return this->parseAllocaInst(parent);
    }
    else if (id == "return")
    {
        return this->parseReturnInst(parent);
    }
    else if (id == "call")
    {
        return this->parseCallInst(parent);
    }
    else
    {
        throw std::runtime_error("Unrecognized instruction name");
    }
}
} // namespace ionir
