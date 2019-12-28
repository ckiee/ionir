#pragma once

#include <optional>
#include <string>
#include <ionir/construct/expr/expr.h>
#include <ionir/construct/expr/id.h>
#include <ionir/construct/values/integer.h>
#include <ionir/construct/values/char.h>
#include <ionir/construct/values/string.h>
#include <ionir/construct/insts/inst.h>
#include <ionir/construct/insts/alloca.h>
#include <ionir/construct/insts/return.h>
#include <ionir/construct/insts/branch.h>
#include <ionir/construct/insts/call.h>
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
#include <ionir/reporting/notice.h>
#include <ionir/reporting/notice_context.h>
#include <ionir/reporting/notice_type.h>
#include <ionir/misc/helpers.h>
#include "scope.h"

namespace ionir {
    class Parser {
    protected:
        TokenStream *stream;

        std::vector<Notice> notices;

        TokenIdentifier tokenIdentifier;

        bool withinRange(long value, long from, long to);

        bool is(TokenType type);

        void expect(TokenType type);

        void skipOver(TokenType type);

        NoticeContext createNoticeContext();

        Notice createNotice(NoticeType type, std::string message);

        Ptr<Scope> createScope();

        void pushNotice(NoticeType type, std::string message);

    public:
        Parser(TokenStream *stream);

        std::vector<Notice> getNotices() const;

        Ptr<Construct> parseTopLevel();

        /**
         * Parses a integer literal in the form of
         * long (or integer 64).
         */
        Ptr<IntegerValue> parseInt();

        Ptr<CharValue> parseChar();

        Ptr<StringValue> parseString();

        std::string parseId();

        Ptr<Type> parseType();

        Arg parseArg();

        Ptr<Args> parseArgs();

        Ptr<Prototype> parsePrototype();

        Ptr<Extern> parseExtern();

        Ptr<Function> parseFunction();

        Ptr<Global> parseGlobal();

        Ptr<Value> parseValue();

        Ptr<IdExpr> parseIdExpr();

        std::optional<Ptr<Expr>> parsePrimaryExpr();

        Ptr<Expr> parseBinaryExprRightSide(Ptr<Expr> leftSide, int minimalPrecedence);

        Ptr<Section> parseSection(Ptr<Block> parent);

        Ptr<Block> parseBlock(Ptr<Function> parent);

        Ptr<AllocaInst> parseAllocaInst(Ptr<Section> parent);

        Ptr<ReturnInst> parseReturnInst(Ptr<Section> parent);

        Ptr<BranchInst> parseBranchInst(Ptr<Section> parent);

        Ptr<CallInst> parseCallInst(Ptr<Section> parent);

        /**
         * Parses an instruction, consuming its identifier.
         * Invokes the corresponding parser depending on its
         * identifier.
         */
        Ptr<Inst> parseInst(Ptr<Section> parent);
    };
}
