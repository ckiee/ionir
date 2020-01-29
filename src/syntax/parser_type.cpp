#include <ionir/syntax/parser.h>

namespace ionir {
    OptPtr<Type> Parser::parseType() {
        // Retrieve the current token.
        Token token = this->stream.get();

        // Abstract the token's properties
        std::string tokenValue = token.getValue();
        TokenKind tokenKind = token.getKind();

        bool isPointer = false;

        IONIR_PARSER_ASSERT(Classifier::isType(tokenKind))

        // Type is a pointer.
        if (tokenKind == TokenKind::SymbolStar) {
            isPointer = true;

            // Skip onto and from the star token.
            this->stream.skip(2);
        }

        // Create and return the resulting type construct.
        return std::make_shared<Type>(tokenValue, Util::resolveTypeKind(tokenValue), isPointer);
    }

    OptPtr<Type> Parser::parseTypePrefix() {
        this->skipOver(TokenKind::SymbolBracketL);

        OptPtr<Type> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        this->skipOver(TokenKind::SymbolBracketR);

        return type;
    }

    OptPtr<VoidType> Parser::parseVoidType() {
        // TODO: Fully verify this works (through unit tests). The question is whether Type -> Void type cast will work.
        OptPtr<Type> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        return type->get()->dynamicCast<VoidType>();
    }

    OptPtr<IntegerType> Parser::parseIntegerType() {
        // TODO: Implement.
    }
}
