#pragma once

#include <optional>
#include <string>
#include "construct/expr/expr.h"
#include "construct/expr/id.h"
#include "construct/values/integer.h"
#include "construct/values/char.h"
#include "construct/values/string.h"
#include "construct/insts/inst.h"
#include "construct/insts/alloca.h"
#include "construct/insts/return.h"
#include "construct/insts/branch.h"
#include "construct/insts/call.h"
#include "construct/psuedo/partial_inst.h"
#include "syntax/token.h"
#include "syntax/token_identifier.h"
#include "construct/extern.h"
#include "construct/function.h"
#include "construct/global.h"
#include "construct/psuedo/args.h"
#include "construct/prototype.h"
#include "construct/block.h"
#include "construct/section.h"
#include "reporting/notice.h"
#include "reporting/notice_context.h"
#include "reporting/notice_type.h"
#include "misc/helpers.h"
#include "scope.h"

namespace ionir
{
class Parser
{
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

    Ptr<Block> parseBlock();

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
} // namespace ionir
