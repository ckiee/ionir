#pragma once

#include <memory>
#include <optional>
#include <string>
#include "syntax/token.h"
#include "syntax/token_identifier.h"
#include "ast_constructs/values/integer.h"
#include "ast_constructs/values/char.h"
#include "ast_constructs/values/string.h"
#include "ast_constructs/extern.h"
#include "ast_constructs/function.h"
#include "ast_constructs/global_var.h"
#include "ast_constructs/args.h"
#include "ast_constructs/prototype.h"
#include "ast_constructs/block.h"
#include "ast_constructs/section.h"
#include "ast_constructs/inst.h"
#include "reporting/notice.h"
#include "reporting/notice_context.h"
#include "reporting/notice_type.h"
#include "misc/helpers.h"
#include "ast_constructs/insts/alloca.h"
#include "ast_constructs/insts/return.h"
#include "ast_constructs/insts/branch.h"
#include "ast_constructs/insts/goto.h"
#include "partial_inst.h"

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

    std::optional<Ptr<Construct>> parsePrimaryExpr();

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
