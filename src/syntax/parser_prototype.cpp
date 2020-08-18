#include <ionir/const/const_name.h>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Args> Parser::parseArgs() {
        ionshared::SymbolTable<Arg> args = {};
        bool isInfinite = false;

        do {
            // Skip comma token if applicable.
            if (this->is(TokenKind::SymbolComma)) {
                // Prevent leading, lonely comma.
                if (args.isEmpty()) {
                    return this->noticeSentinel->makeError<Args>(IONIR_NOTICE_FUNCTION_CALL_LEADING_COMMA);
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

    AstPtrResult<Prototype> Parser::parsePrototype(const ionshared::Ptr<Module> &parent) {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolParenthesesL))

        ionshared::Ptr<Args> args = std::make_shared<Args>();

        // Parse arguments if applicable.
        if (!this->is(TokenKind::SymbolParenthesesR)) {
            AstPtrResult<Args> temporaryArgs = this->parseArgs();

            IONIR_PARSER_ASSURE(temporaryArgs)

            args = Util::getResultPtrValue(temporaryArgs);
        }

        this->stream.skip();

        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolArrow))

        AstPtrResult<Type> returnType = this->parseType();

        IONIR_PARSER_ASSURE(returnType)

        return std::make_shared<Prototype>(*id, args, Util::getResultPtrValue(returnType), parent);
    }

    AstPtrResult<Extern> Parser::parseExtern(const ionshared::Ptr<Module> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordExtern))

        AstPtrResult<Prototype> prototype = this->parsePrototype(parent);

        IONIR_PARSER_ASSURE(prototype)

        return std::make_shared<Extern>(Util::getResultPtrValue(prototype));
    }

    AstPtrResult<Function> Parser::parseFunction(const ionshared::Ptr<Module> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordFunction))

        AstPtrResult<Prototype> prototype = this->parsePrototype(parent);
        AstPtrResult<FunctionBody> body = this->parseFunctionBody(nullptr);

        IONIR_PARSER_ASSURE(prototype)
        IONIR_PARSER_ASSURE(body)

        ionshared::Ptr<Function> function =
            std::make_shared<Function>(
                Util::getResultPtrValue(prototype),
                Util::getResultPtrValue(body)
            );

        body->get()->setParent(function);

        return function;
    }
}
