#include <utility>
#include <ionir/const/const.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    std::optional<std::string> Parser::parseId() {
        this->skipOver(TokenKind::OperatorModulo);

        // TODO: No error?
        if (!this->is(TokenKind::Identifier)) {
            return std::nullopt;
        }

        Token id = this->tokenStream->get();

        // Skip over identifier token.
        this->tokenStream->skip();

        // Return the identifier's value.
        return id.getValue();
    }

    AstResult<Arg> Parser::parseArg() {
        AstPtrResult<Type> type = this->parseType();

        // TODO: Function does not return a pointer. No assert is specialized for that case.
//        IONIR_PARSER_ASSERT_RESULT(type, Arg)
        if (!util::hasValue(type)) {
            throw std::runtime_error("Not implemented");
        }

        std::optional<std::string> id = this->parseId();

        // TODO: Function does not return a pointer. No assert is specialized for that case.
        //        IONIR_PARSER_ASSERT_VALUE(id, Arg)
        if (!id.has_value()) {
            throw std::runtime_error("Not implemented");
        }

        return std::make_pair(util::getResultValue(type), *id);
    }
}
