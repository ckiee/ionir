#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Value<>> Parser::parseValue() {
        TokenKind currentTokenKind = this->tokenStream->get().getKind();

        /**
         * Must use static pointer cast when downcasting to Value<>, given
         * Value's template argument.
         */
        switch (currentTokenKind) {
            case TokenKind::LiteralInteger: {
                // TODO: Should be done like below...
                return util::getResultValue(this->parseIntegerLiteral())->staticCast<Value<>>();

                // TODO: Throwing error for some reason.
//                return util::castAstPtrResult<IntegerValue, Value<>>(
//                    this->parseInt(),
//                    false
//                );
            }

            case TokenKind::LiteralCharacter: {
                // TODO: Should be done like below...
                return util::getResultValue(this->parseCharLiteral())->staticCast<Value<>>();

                // TODO: Throwing error for some reason.
//                return util::castAstPtrResult<CharValue, Value<>>(
//                    this->parseChar(),
//                    false
//                );
            }

            case TokenKind::LiteralString: {
                return util::castAstPtrResult<StringLiteral, Value<>>(
                    this->parseStringLiteral(),
                    false
                );
            }

            // TODO: Missing values.

            default: {
                return this->noticeSentinel->makeError<Value<>>(
                    IONIR_NOTICE_MISC_UNEXPECTED_TOKEN
                );
            }
        }
    }

    AstPtrResult<IntegerLiteral> Parser::parseIntegerLiteral() {
        IONIR_PARSER_TOKEN_KIND(TokenKind::LiteralInteger, IntegerLiteral)

        /**
         * Abstract the token's value to be used in the
         * string to long integer conversion.
         */
        std::string tokenValue = this->tokenStream->get().getValue();

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
            return this->noticeSentinel->makeError<IntegerLiteral>(
                IONIR_NOTICE_VALUE_CONVERT_STRING_TO_INT_FAILED
            );
        }

        // Calculate the value's bit-length and it's corresponding integer kind.
        uint32_t valueBitLength = ionshared::util::calculateBitLength(value);

        std::optional<IntegerKind> valueIntegerKind =
            util::findIntegerKindFromBitLength(valueBitLength);

        if (!valueIntegerKind.has_value()) {
            // TODO: Hard-coded message. Use consts.
            return this->noticeSentinel->makeError<IntegerLiteral>("Integer value's type kind could not be determined");
        }

        /**
         * Default integers to 32-bit lengths. Use implicit casts later
         * on if they must be used differently. Although technically inefficient
         * in terms of storage, modern processors are built to handle integers of
         * 32-64 bit lengths more efficiently. So it's a small space sacrifice for
         * default performance.
         */
        if (*valueIntegerKind < IntegerKind::Int32) {
            valueIntegerKind = IntegerKind::Int32;
        }

        // Create a long integer type for the value.
        ionshared::Ptr<IntegerType> type =
            std::make_shared<IntegerType>(*valueIntegerKind);

        // Create the integer instance.
        ionshared::Ptr<IntegerLiteral> integer =
            std::make_shared<IntegerLiteral>(type, value);

        // Skip current token.
        this->tokenStream->tryNext();

        // Finally, return the result.
        return integer;
    }

    AstPtrResult<CharLiteral> Parser::parseCharLiteral() {
        IONIR_PARSER_TOKEN_KIND(TokenKind::LiteralCharacter, CharLiteral)

        // Extract the value from the character token.
        std::string stringValue = this->tokenStream->get().getValue();

        // Skip over character token.
        this->tokenStream->skip();

        // Ensure extracted value only contains a single character.
        if (stringValue.length() > 1) {
            return this->noticeSentinel->makeError<CharLiteral>(IONIR_NOTICE_VALUE_CHARACTER_MAX_ONE);
        }

        // Create the character construct with the first and only character of the captured value.
        return std::make_shared<CharLiteral>(stringValue[0]);
    }

    AstPtrResult<StringLiteral> Parser::parseStringLiteral() {
        IONIR_PARSER_TOKEN_KIND(TokenKind::LiteralString, StringLiteral)

        // Extract the value from the string token.
        std::string value = this->tokenStream->get().getValue();

        // Skip over string token.
        this->tokenStream->skip();

        return std::make_shared<StringLiteral>(value);
    }
}
