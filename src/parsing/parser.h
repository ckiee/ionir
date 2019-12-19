#pragma once

#include <memory>
#include <optional>
#include <string>
#include "constructs/expr/expr.h"
#include "constructs/expr/id.h"
#include "constructs/values/integer.h"
#include "constructs/values/char.h"
#include "constructs/values/string.h"
#include "constructs/insts/inst.h"
#include "constructs/insts/alloca.h"
#include "constructs/insts/return.h"
#include "constructs/insts/branch.h"
#include "constructs/insts/goto.h"
#include "constructs/psuedo/partial_inst.h"
#include "syntax/token.h"
#include "syntax/token_identifier.h"
#include "constructs/extern.h"
#include "constructs/function.h"
#include "constructs/global_var.h"
#include "constructs/args.h"
#include "constructs/prototype.h"
#include "constructs/block.h"
#include "constructs/section.h"
#include "reporting/notice.h"
#include "reporting/notice_context.h"
#include "reporting/notice_type.h"
#include "misc/helpers.h"

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

    Ptr<GlobalVar> parseGlobalVar();

    Ptr<Value> parseValue();

    Ptr<IdExpr> parseIdExpr();

    std::optional<Ptr<Expr>> parsePrimaryExpr();

    Ptr<Construct> parseBinaryExprRightSide(Ptr<Construct> leftSide, int minimalPrecedence);

    Ptr<Section> parseSection();

    Ptr<Block> parseBlock();

    Ptr<AllocaInst> parseAllocaInst();

    Ptr<ReturnInst> parseReturnInst();

    Ptr<BranchInst> parseBranchInst();

    Ptr<GotoInst> parseGotoInst();

    /**
     * Parses an instruction, consuming its identifier.
     * Invokes the corresponding parser depending on its
     * identifier.
     */
    Ptr<Inst> parseInst();
};
} // namespace ionir
