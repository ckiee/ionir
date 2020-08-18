#include <utility>
#include <ionir/const/const.h>
#include <ionir/syntax/parser.h>

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
        AstPtrResult<Type> type = this->parseType();

        this->assertHasValue(type);

        std::optional<std::string> id = this->parseId();

        this->assertHasValue(id);

        return std::make_pair(Util::getResultPtrValue(type), *id);
    }
}
