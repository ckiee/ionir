#include <ionir/const/const.h>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    // TODO: Consider using Ref<> to register pending type reference if user-defined type is parsed?
    AstPtrResult<Type> Parser::parseType() {
        // Retrieve the current token.
        Token token = this->stream.get();

        // Abstract the token's properties
        std::string tokenValue = token.getValue();
        TokenKind tokenKind = token.getKind();

        this->assertOrError((
            Classifier::isType(tokenKind)
            || tokenKind == TokenKind::Identifier
        ));

        AstPtrResult<Type> type;

        if (tokenKind == TokenKind::TypeVoid) {
            type = Util::convertAstPtrResult<VoidType, Type>(
                this->parseVoidType()
            );
        }
        else if (Classifier::isIntegerType(tokenKind)) {
            type = Util::convertAstPtrResult<IntegerType, Type>(
                this->parseIntegerType()
            );
        }

        // TODO: Add support for missing types.

        /**
         * Type could not be identified as integer nor void type, attempt
         * to resolve its an internal type kind from the token's value,
         * otherwise default to an user-defined type assumption.
         */
        if (!Util::hasValue(type)) {
            type = std::make_shared<Type>(tokenValue, Util::resolveTypeKind(tokenValue));
            this->stream.skip();
        }

        // If applicable, mark the type as a pointer.
        if (this->is(TokenKind::SymbolStar)) {
            // TODO: CRITICAL: Pointer must be an expression, since what about **?
            // TODO: New! 8/17/2020: No longer are types 'marked' as pointers. Instead, there's a full Pointer type now. Make changes to reflect this.
            /**
             * Only mark the type as a pointer if marked so
             * by the star symbol. Since some types (for example
             * the char type) are pointers by default, using a flag
             * in this case would prevent it from being a pointer
             * unless a star symbol is present.
             */
//            type->get()->setIsPointer(true);

            // Skip from the star token.
            this->stream.skip();
        }

        // Create and return the resulting type construct.
        return type;
    }

    AstPtrResult<Type> Parser::parseTypePrefix() {
        this->assertOrError(this->skipOver(TokenKind::SymbolBracketL));

        AstPtrResult<Type> type = this->parseType();

        this->assertHasValue(type);
        this->assertOrError(this->skipOver(TokenKind::SymbolBracketR));

        return type;
    }

    AstPtrResult<VoidType> Parser::parseVoidType() {
        /**
         * Void type does not accept references nor pointer
         * specifiers, so just simply skip over its token.
         */
        this->skipOver(TokenKind::TypeVoid);

        return std::make_shared<VoidType>();
    }

    AstPtrResult<IntegerType> Parser::parseIntegerType() {
        TokenKind currentTokenKind = this->stream.get().getKind();

        if (!Classifier::isIntegerType(currentTokenKind)) {
            return this->noticeSentinel->makeError<IntegerType>(IONIR_NOTICE_MISC_UNEXPECTED_TOKEN);
        }

        // TODO: Missing support for is signed or not, as well as is pointer.

        std::optional<IntegerKind> integerKind = Const::getIntegerKind(currentTokenKind);

        this->assertHasValue(integerKind);

        // Skip over the type token.
        this->stream.skip();

        return std::make_shared<IntegerType>(*integerKind);
    }
}
