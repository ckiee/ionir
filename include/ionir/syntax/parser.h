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
#include <ionir/lexical/classifier.h>
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
    class Parser {
    private:
        TokenStream stream;

        StackTrace stackTrace;

        std::string filePath;

        Classifier tokenIdentifier;

    protected:
        Classifier getTokenIdentifier() const;

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

        OptPtr<Construct> parseTopLevel();

        /**
         * Parses a integer literal in the form of
         * long (or integer 64).
         */
        OptPtr<IntegerValue> parseInt();

        OptPtr<CharValue> parseChar();

        OptPtr<StringValue> parseString();

        std::optional<std::string> parseId();

        OptPtr<Type> parseType();

        OptPtr<Type> parseTypePrefix();

        OptPtr<VoidType> parseVoidType();

        OptPtr<IntegerType> parseIntegerType();

        std::optional<Arg> parseArg();

        OptPtr<Args> parseArgs();

        OptPtr<Prototype> parsePrototype();

        OptPtr<Extern> parseExtern();

        OptPtr<Function> parseFunction();

        OptPtr<Global> parseGlobal();

        OptPtr<Value<>> parseValue();

        OptPtr<IdExpr> parseIdExpr();

        OptPtr<Expr<>> parsePrimaryExpr();

        OptPtr<Expr<>> parseBinaryExprRightSide(Ptr<Expr<>> leftSide, int minimalPrecedence);

        OptPtr<Section> parseSection(Ptr<Block> parent);

        OptPtr<Block> parseBlock(Ptr<Function> parent);

        OptPtr<AllocaInst> parseAllocaInst(Ptr<Section> parent);

        OptPtr<ReturnInst> parseReturnInst(Ptr<Section> parent);

        OptPtr<BranchInst> parseBranchInst(Ptr<Section> parent);

        OptPtr<CallInst> parseCallInst(Ptr<Section> parent);

        OptPtr<StoreInst> parseStoreInst(Ptr<Section> parent);

        /**
         * Parses an instruction, consuming its identifier.
         * Invokes the corresponding parser depending on its
         * identifier.
         */
        OptPtr<Inst> parseInst(Ptr<Section> parent);

        OptPtr<Module> parseModule();

        std::optional<std::string> parseLine();

        // TODO: Add comment-parsing support.

        std::optional<Directive> parseDirective();

        template<typename T = Construct>
        OptPtr<Ref<T>> parseRef(Ptr<Construct> owner) {
            std::optional<std::string> id = this->parseId();

            IONIR_PARSER_ASSURE(id)

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
