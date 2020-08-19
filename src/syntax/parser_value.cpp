#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Value<>> Parser::parseValue() {
        Token token = this->stream.get();

        switch (token.getKind()) {
            case TokenKind::LiteralInteger: {
                return Util::convertAstPtrResult<IntegerValue, Value<>>(this->parseInt());
            }

            case TokenKind::LiteralCharacter: {
                return Util::convertAstPtrResult<CharValue, Value<>>(this->parseChar());
            }

            // TODO: Missing values.

            default: {
                return this->noticeSentinel->makeError<Value<>>(IONIR_NOTICE_MISC_UNEXPECTED_TOKEN);
            }
        }
    }

    AstPtrResult<IntegerValue> Parser::parseInt() {
        this->assertTokenKind(TokenKind::LiteralInteger);

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
            // TODO: Need to add support for 128-bit length.
            /**
             * May throw an exception if invalid arguments are provided,
             * or of the integer is too large to be held in any integer
             * type native to C++ (maximum is 64-bit length).
             */
            value = std::stoll(tokenValue);
        }
        catch (std::exception& exception) {
            // Value conversion failed.
            return this->noticeSentinel->makeError<IntegerValue>(
                IONIR_NOTICE_VALUE_CONVERT_STRING_TO_INT_FAILED
            );
        }

        // Calculate the value's bit-length and it's corresponding integer kind.
        uint32_t valueBitLength = ionshared::Util::calculateBitLength(value);

        std::optional<IntegerKind> valueIntegerKind =
            Util::calculateIntegerKindFromBitLength(valueBitLength);

        if (!valueIntegerKind.has_value()) {
            // TODO: Hard-coded message. Use consts.
            return this->noticeSentinel->makeError<IntegerValue>("Integer value's type kind could not be determined");
        }

        // Create a long integer type for the value.
        ionshared::Ptr<IntegerType> type = std::make_shared<IntegerType>(*valueIntegerKind);

        // Create the integer instance.
        ionshared::Ptr<IntegerValue> integer = std::make_shared<IntegerValue>(type, value);

        // Skip current token.
        this->stream.tryNext();

        // Finally, return the result.
        return integer;
    }

    AstPtrResult<CharValue> Parser::parseChar() {
        this->assertTokenKind(TokenKind::LiteralCharacter);

        // Extract the value from the character token.
        std::string stringValue = this->stream.get().getValue();

        // Skip over character token.
        this->stream.skip();

        // Ensure extracted value only contains a single character.
        if (stringValue.length() > 1) {
            return this->noticeSentinel->makeError<CharValue>(IONIR_NOTICE_VALUE_CHARACTER_MAX_ONE);
        }

        // Create the character construct with the first and only character of the captured value.
        return std::make_shared<CharValue>(stringValue[0]);
    }

    AstPtrResult<StringValue> Parser::parseString() {
        this->assertTokenKind(TokenKind::LiteralString);

        // Extract the value from the string token.
        std::string value = this->stream.get().getValue();

        // Skip over string token.
        this->stream.skip();

        return std::make_shared<StringValue>(value);
    }
}
