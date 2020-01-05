#include <vector>
#include <ionir/construct/expr.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    std::optional<Ptr<Args>> Parser::parseArgs() {
        std::vector<Arg> args = {};
        bool isInfinite = false;

        do {
            // Skip comma token if applicable.
            if (this->is(TokenKind::SymbolComma)) {
                // Prevent leading, lonely comma.
                if (args.size() == 0) {
                    return this->makeNotice("Leading comma in argument list is not allowed");
                }

                // Skip over comma token.
                this->stream.next();
            }

            std::optional<Arg> arg = this->parseArg();

            IONIR_PARSER_ASSURE(arg)

            // Parse arg and push onto the vector.
            args.push_back(*arg);
        } while (this->is(TokenKind::SymbolComma));

        return std::make_shared<Args>(args, isInfinite);
    }

    std::optional<Ptr<Prototype>> Parser::parsePrototype() {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        this->skipOver(TokenKind::SymbolParenthesesL);

        Ptr<Args> args = std::make_shared<Args>();

        // Parse arguments if applicable.
        if (!this->is(TokenKind::SymbolParenthesesR)) {
            std::optional<Ptr<Args>> temporaryArgs = this->parseArgs();

            IONIR_PARSER_ASSURE(temporaryArgs)

            args = *temporaryArgs;
        }

        this->stream.skip();
        this->skipOver(TokenKind::SymbolArrow);

        std::optional<Ptr<Type>> returnType = this->parseType();

        IONIR_PARSER_ASSURE(returnType)

        return std::make_shared<Prototype>(*id, args, *returnType);
    }

    std::optional<Ptr<Extern>> Parser::parseExtern() {
        this->skipOver(TokenKind::KeywordExtern);

        std::optional<Ptr<Prototype>> prototype = this->parsePrototype();

        IONIR_PARSER_ASSURE(prototype)

        return std::make_shared<Extern>(*prototype);
    }

    std::optional<Ptr<Function>> Parser::parseFunction() {
        this->skipOver(TokenKind::KeywordFunction);

        std::optional<Ptr<Prototype>> prototype = this->parsePrototype();
        std::optional<Ptr<Block>> body = this->parseBlock(nullptr);

        IONIR_PARSER_ASSURE(prototype)
        IONIR_PARSER_ASSURE(body)

        Ptr<Function> function = std::make_shared<Function>(*prototype, *body);

        body->get()->setParent(function);

        return function;
    }
}
