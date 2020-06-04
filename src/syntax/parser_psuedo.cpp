#include <utility>
#include <ionir/const/const.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    std::optional<std::string> Parser::parseId() {
        this->skipOver(TokenKind::OperatorModulo);

        IONIR_PARSER_EXPECT(TokenKind::Identifier)

        Token id = this->stream.get();

        // Skip over identifier token.
        this->stream.skip();

        // Return the identifier's value.
        return id.getValue();
    }

    std::optional<Arg> Parser::parseArg() {
        std::optional<Ptr<Type>> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        return std::make_pair(*type, *id);
    }
}
