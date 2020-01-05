#pragma once

#include <optional>
#include <string>
#include <ionir/construct/expr/expr.h>
#include <ionir/construct/expr/id.h>
#include <ionir/construct/value/integer.h>
#include <ionir/construct/value/char.h>
#include <ionir/construct/value/string.h>
#include <ionir/construct/inst/inst.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/inst/store.h>
#include <ionir/construct/psuedo/partial_inst.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/token_identifier.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/function.h>
#include <ionir/construct/global.h>
#include <ionir/construct/psuedo/args.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/block.h>
#include <ionir/construct/section.h>
#include <ionir/reporting/notice_factory.h>
#include <ionir/misc/helpers.h>
#include <ionir/const/const_name.h>
#include "scope.h"

namespace ionir {
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
            const std::string filePath = ConstName::anonymous);

        StackTrace getStackTrace() const;

        std::string getFilePath() const;

        std::optional<Ptr<Construct>> parseTopLevel();

        /**
         * Parses a integer literal in the form of
         * long (or integer 64).
         */
        std::optional<Ptr<IntegerValue >> parseInt();

        std::optional<Ptr<CharValue>> parseChar();

        std::optional<Ptr<StringValue>> parseString();

        std::optional<std::string> parseId();

        std::optional<Ptr<Type>> parseType();

        std::optional<Arg> parseArg();

        std::optional<Ptr<Args>> parseArgs();

        std::optional<Ptr<Prototype>> parsePrototype();

        std::optional<Ptr<Extern>> parseExtern();

        std::optional<Ptr<Function>> parseFunction();

        std::optional<Ptr<Global>> parseGlobal();

        std::optional<Ptr<Value>> parseValue();

        std::optional<Ptr<IdExpr>> parseIdExpr();

        std::optional<Ptr<Expr>> parsePrimaryExpr();

        std::optional<Ptr<Expr>> parseBinaryExprRightSide(Ptr<Expr> leftSide, int minimalPrecedence);

        std::optional<Ptr<Section>> parseSection(Ptr<Block> parent);

        std::optional<Ptr<Block>> parseBlock(Ptr<Function> parent);

        std::optional<Ptr<AllocaInst>> parseAllocaInst(Ptr<Section> parent);

        std::optional<Ptr<ReturnInst>> parseReturnInst(Ptr<Section> parent);

        std::optional<Ptr<BranchInst>> parseBranchInst(Ptr<Section> parent);

        std::optional<Ptr<CallInst>> parseCallInst(Ptr<Section> parent);

        std::optional<Ptr<StoreInst>> parseStoreInst(Ptr<Section> parent);

        /**
         * Parses an instruction, consuming its identifier.
         * Invokes the corresponding parser depending on its
         * identifier.
         */
        std::optional<Ptr<Inst>> parseInst(Ptr<Section> parent);
    };
}
