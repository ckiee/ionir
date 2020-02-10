#include <ionir/construct/expr.h>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    OptPtr<Value<>> Parser::parseValue() {
        Token token = this->stream.get();

        switch (token.getKind()) {
            case TokenKind::LiteralInt: {
                OptPtr<IntegerValue> integerValue = this->parseInt();

                if (integerValue.has_value()) {
                    return integerValue->get()->dynamicCast<Value<>>();
                }

                return std::nullopt;
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

    OptPtr<IntegerValue> Parser::parseInt() {
        OptPtr<Type> type = this->parseTypePrefix();

        IONIR_PARSER_ASSURE(type)
        IONIR_PARSER_EXPECT(TokenKind::LiteralInt)

        /**
         * Abstract the token's value to be used in the
         * string to long integer conversion.
         */
        std::string tokenValue = this->stream.get().getValue();

        // TODO: May stol() throw an error? If so, wrap in try-catch block for safety.
        /**
         * Attempt to convert token's value to a long
         * (int64_t for cross-platform support).
         */
        int64_t value;

        try {
            value = std::stol(tokenValue);
        }
        catch (std::invalid_argument& exception) {
            // Value conversion failed.
            return this->makeNotice("Could not convert string to value");
        }

        // TODO: Cannot cast Type to IntegerType just like that. It will have missing values (ex.
        // Create the integer instance.
        Ptr<IntegerValue> integer =
            std::make_shared<IntegerValue>((*type)->dynamicCast<IntegerType>(), value);

        // Skip current token.
        this->stream.tryNext();

        // Finally, return the result.
        return integer;
    }

    OptPtr<CharValue> Parser::parseChar() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralCharacter);

        // Extract the value from the character token.
        std::string stringValue = this->stream.get().getValue();

        // Skip over character token.
        this->stream.skip();

        // Ensure extracted value only contains a single character.
        if (stringValue.length() > 1) {
            return this->makeNotice("Character value length must be at most 1 character");
        }

        // Create the character construct with the first and only character of the captured value.
        return std::make_shared<CharValue>(stringValue[0]);
    }

    OptPtr<StringValue> Parser::parseString() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralString);

        // Extract the value from the string token.
        std::string value = this->stream.get().getValue();

        // Skip over string token.
        this->stream.skip();

        return std::make_shared<StringValue>(value);
    }
}
