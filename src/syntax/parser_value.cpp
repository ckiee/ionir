#include <climits>
#include <utility>
#include <vector>
#include <ionir/construct/expr.h>
#include <ionir/construct/expr/binary_expr.h>
#include <ionir/misc/util.h>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    std::optional<Ptr<Value>> Parser::parseValue() {
        Token token = this->stream.get();

        switch (token.getKind()) {
            case TokenKind::LiteralInt: {
                return this->parseInt();
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

    std::optional<Ptr<IntegerValue>> Parser::parseInt() {
        std::optional<Ptr<Type>> type = this->parseTypePrefix();

        IONIR_PARSER_ASSURE(type)
        IONIR_PARSER_EXPECT(TokenKind::LiteralInt)

        // Abstract the token's value to be used in the string -> long conversion.
        std::string tokenValue = this->stream.get().getValue();

        // TODO: May stol() throw an error? If so, wrap in try-catch block for safety.
        // Attempt to convert token's value to a long (int64_t for cross-platform support).
        int64_t value = std::stol(tokenValue);

        // Create the integer instance.
        Ptr<IntegerValue> integer = std::make_shared<IntegerValue>(type->get()->cast<IntegerType>(), value);

        // Skip current token.
        this->stream.tryNext();

        // Finally, return the result.
        return integer;
    }

    std::optional<Ptr<CharValue>> Parser::parseChar() {
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

    std::optional<Ptr<StringValue>> Parser::parseString() {
        IONIR_PARSER_EXPECT(TokenKind::LiteralString);

        // Extract the value from the string token.
        std::string value = this->stream.get().getValue();

        // Skip over string token.
        this->stream.skip();

        return std::make_shared<StringValue>(value);
    }
}
