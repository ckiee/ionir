#include <ionir/const/const_name.h>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Args> Parser::parseArgs() {
        ionshared::SymbolTable<Arg> args = ionshared::SymbolTable<Arg>();
        bool isInfinite = false;

        do {
            // Skip comma token if applicable.
            if (this->is(TokenKind::SymbolComma)) {
                // Prevent leading, lonely comma.
                if (args.isEmpty()) {
                    return this->noticeSentinel->makeError<Args>(IONIR_NOTICE_FUNCTION_CALL_LEADING_COMMA);
                }

                // Skip over comma token.
                this->tokenStream->next();
            }

            AstResult<Arg> argResult = this->parseArg();

            IONIR_PARSER_ASSERT_RESULT(argResult, Args)

            Arg arg = util::getResultValue(argResult);

            // Set the argument on the symbol table.
            args[arg.second] = arg;
        }
        while (this->is(TokenKind::SymbolComma));

        return std::make_shared<Args>(args, isInfinite);
    }

    AstPtrResult<Prototype> Parser::parsePrototype(const ionshared::Ptr<Module> &parent) {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(id, Prototype)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolParenthesesL), Prototype)

        ionshared::Ptr<Args> args = std::make_shared<Args>();

        // Parse arguments if applicable.
        if (!this->is(TokenKind::SymbolParenthesesR)) {
            AstPtrResult<Args> temporaryArgs = this->parseArgs();

            IONIR_PARSER_ASSERT_RESULT(temporaryArgs, Prototype)

            args = util::getResultValue(temporaryArgs);
        }

        this->tokenStream->skip();
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolArrow), Prototype)

        AstPtrResult<Type> returnType = this->parseType();

        IONIR_PARSER_ASSERT_RESULT(returnType, Prototype)

        return std::make_shared<Prototype>(*id, args, util::getResultValue(returnType), parent);
    }

    AstPtrResult<Extern> Parser::parseExtern(const ionshared::Ptr<Module> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordExtern), Extern)

        AstPtrResult<Prototype> prototype = this->parsePrototype(parent);

        IONIR_PARSER_ASSERT_RESULT(prototype, Extern)
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolSemiColon), Extern)

        return std::make_shared<Extern>(util::getResultValue(prototype));
    }

    AstPtrResult<Function> Parser::parseFunction(const ionshared::Ptr<Module> &parent) {
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::KeywordFunction), Function)

        AstPtrResult<Prototype> prototype = this->parsePrototype(parent);

        // Parent will be filled in below.
        AstPtrResult<FunctionBody> bodyResult = this->parseFunctionBody(nullptr);

        IONIR_PARSER_ASSERT_RESULT(prototype, Function)
        IONIR_PARSER_ASSERT_RESULT(bodyResult, Function)

        ionshared::Ptr<FunctionBody> functionBody = util::getResultValue(bodyResult);

        ionshared::Ptr<Function> function = std::make_shared<Function>(
            util::getResultValue(prototype),
            functionBody
        );

        // Fill in the function body's parent.
        functionBody->setParent(function);

        return function;
    }
}
