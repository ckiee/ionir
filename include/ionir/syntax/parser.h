#pragma once

#include <optional>
#include <string>
#include <ionir/construct/expr.h>
#include <ionir/construct/expr/id.h>
#include <ionir/construct/value/integer.h>
#include <ionir/construct/value/char.h>
#include <ionir/construct/value/string.h>
#include <ionir/construct/inst.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/inst/store.h>
#include <ionir/construct/pseudo/partial_inst.h>
#include <ionir/construct/pseudo/directive.h>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/token_identifier.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/function.h>
#include <ionir/construct/global.h>
#include <ionir/construct/pseudo/args.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/block.h>
#include <ionir/construct/section.h>
#include <ionir/construct/module.h>
#include <ionir/reporting/notice_factory.h>
#include <ionir/misc/helpers.h>
#include <ionir/const/const_name.h>
#include "scope.h"
#include "parser_helpers.h"

namespace ionir {
    template<typename T>
    using ParserResult = OptPtr<T>;

    class Parser {
    private:
        TokenStream stream;

        StackTrace stackTrace;

        std::string filePath;

        TokenIdentifier tokenIdentifier;

    protected:
        TokenIdentifier getTokenIdentifier() const;

        bool is(TokenKind tokenKind);

        bool expect(TokenKind tokenKind);

        void skipOver(TokenKind tokenKind);

        NoticeFactory createNoticeFactory();

        std::nullopt_t makeNotice(std::string message, NoticeType type = NoticeType::Error);

    public:
        explicit Parser(TokenStream stream, StackTrace stackTrace = {},
            std::string filePath = ConstName::anonymous);

        StackTrace getStackTrace() const;

        std::string getFilePath() const;

        ParserResult<Construct> parseTopLevel();

        /**
         * Parses a integer literal in the form of
         * long (or integer 64).
         */
        ParserResult<IntegerValue> parseInt();

        ParserResult<CharValue> parseChar();

        ParserResult<StringValue> parseString();

        std::optional<std::string> parseId();

        ParserResult<Type> parseType();

        ParserResult<Type> parseTypePrefix();

        std::optional<Arg> parseArg();

        ParserResult<Args> parseArgs();

        ParserResult<Prototype> parsePrototype();

        ParserResult<Extern> parseExtern();

        ParserResult<Function> parseFunction();

        ParserResult<Global> parseGlobal();

        ParserResult<Value<>> parseValue();

        ParserResult<IdExpr> parseIdExpr();

        ParserResult<Expr<>> parsePrimaryExpr();

        ParserResult<Expr<>> parseBinaryExprRightSide(Ptr<Expr<>> leftSide, int minimalPrecedence);

        ParserResult<Section> parseSection(Ptr<Block> parent);

        ParserResult<Block> parseBlock(Ptr<Function> parent);

        ParserResult<AllocaInst> parseAllocaInst(Ptr<Section> parent);

        ParserResult<ReturnInst> parseReturnInst(Ptr<Section> parent);

        ParserResult<BranchInst> parseBranchInst(Ptr<Section> parent);

        ParserResult<CallInst> parseCallInst(Ptr<Section> parent);

        ParserResult<StoreInst> parseStoreInst(Ptr<Section> parent);

        /**
         * Parses an instruction, consuming its identifier.
         * Invokes the corresponding parser depending on its
         * identifier.
         */
        ParserResult<Inst> parseInst(Ptr<Section> parent);

        ParserResult<Module> parseModule();

        std::optional<std::string> parseLine();

        // TODO: Add comment-parsing support.

        std::optional<Directive> parseDirective();

        template<typename T = Construct>
        ParserResult<Ref<T>> parseReference(Ptr<Construct> owner) {
            std::optional<std::string> id = this->parseId();

            IONIR_PARSER_ASSURE(id)

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
