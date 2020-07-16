#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    ionshared::OptPtr<Args> Parser::parseArgs() {
        SymbolTable<Arg> args = {};
        bool isInfinite = false;

        do {
            // Skip comma token if applicable.
            if (this->is(TokenKind::SymbolComma)) {
                // Prevent leading, lonely comma.
                if (args.isEmpty()) {
                    return this->makeNotice("Leading comma in argument list is not allowed");
                }

                // Skip over comma token.
                this->stream.next();
            }

            std::optional<Arg> arg = this->parseArg();

            IONIR_PARSER_ASSURE(arg)

            // Set the argument on the symbol table.
            args[arg->second] = *arg;
        }
        while (this->is(TokenKind::SymbolComma));

        return std::make_shared<Args>(args, isInfinite);
    }

    ionshared::OptPtr<Prototype> Parser::parsePrototype(ionshared::Ptr<Module> parent) {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolParenthesesL))

        ionshared::Ptr<Args> args = std::make_shared<Args>();

        // Parse arguments if applicable.
        if (!this->is(TokenKind::SymbolParenthesesR)) {
            std::optional<ionshared::Ptr<Args>> temporaryArgs = this->parseArgs();

            IONIR_PARSER_ASSURE(temporaryArgs)

            args = *temporaryArgs;
        }

        this->stream.skip();

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolArrow))

        ionshared::OptPtr<Type> returnType = this->parseType();

        IONIR_PARSER_ASSURE(returnType)

        return std::make_shared<Prototype>(*id, args, *returnType, parent);
    }

    ionshared::OptPtr<Extern> Parser::parseExtern(ionshared::Ptr<Module> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordExtern))

        ionshared::OptPtr<Prototype> prototype = this->parsePrototype(parent);

        IONIR_PARSER_ASSURE(prototype)

        return std::make_shared<Extern>(*prototype);
    }

    ionshared::OptPtr<Function> Parser::parseFunction(ionshared::Ptr<Module> parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordFunction))

        ionshared::OptPtr<Prototype> prototype = this->parsePrototype(parent);
        ionshared::OptPtr<FunctionBody> body = this->parseFunctionBody(nullptr);

        IONIR_PARSER_ASSURE(prototype)
        IONIR_PARSER_ASSURE(body)

        ionshared::Ptr<Function> function = std::make_shared<Function>(*prototype, *body);

        body->get()->setParent(function);

        return function;
    }
}
