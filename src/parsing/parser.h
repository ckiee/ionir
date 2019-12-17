#pragma once

#include <memory>
#include <optional>
#include <string>
#include "syntax/token.h"
#include "syntax/token_identifier.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/function.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/args.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"
#include "ast_nodes/section.h"
#include "ast_nodes/inst.h"
#include "misc/notice.h"
#include "misc/notice_context.h"
#include "misc/notice_type.h"
#include "misc/helpers.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/return.h"
#include "ast_nodes/insts/branch.h"
#include "ast_nodes/insts/goto.h"
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

    Ptr<Node> parseTopLevel();

    /**
     * Parses a integer literal in the form of
     * long (or integer 64).
     */
    Ptr<IntValue> parseInt();

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

    std::optional<Ptr<Node>> parsePrimaryExpr();

    Ptr<Node> parseBinaryExprRightSide(Ptr<Node> leftSide, int minimalPrecedence);

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
