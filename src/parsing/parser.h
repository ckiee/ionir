#pragma once

#include <optional>
#include <string>
#include "syntax/token.h"
#include "syntax/token_identifier.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/args.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"
#include "ast_nodes/section.h"
#include "ast_nodes/inst.h"
#include "misc/notice.h"
#include "misc/notice_context.h"
#include "misc/notice_type.h"
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
    TokenStream stream;

    std::vector<Notice> notices;

    TokenIdentifier tokenIdentifier;

    bool withinRange(long value, long from, long to);

    bool is(TokenType type);

    void expect(TokenType type);

    void skipOver(TokenType type);

    NoticeContext createNoticeContext();

    Notice createNotice(NoticeType type, std::string message);

    void pushNotice(NoticeType type, std::string message);

public:
    Parser(TokenStream stream);

    std::vector<Notice> getNotices() const;

    /**
     * Parses a integer literal in the form of
     * long (or integer 64).
     */
    IntValue *parseInt();

    CharValue *parseChar();

    StringValue *parseString();

    std::string parseIdentifier();

    Type *parseType();

    Arg parseArg();

    Args parseArgs();

    Prototype *parsePrototype();

    Extern *parseExtern();

    Section *parseSection();

    Block *parseBlock();

    Value *parseValue();

    std::optional<Node *> parsePrimaryExpr();

    Node *parseBinaryExprRightSide(Node *leftSide, int minimalPrecedence);

    AllocaInst *parseAllocaInst();

    ReturnInst *parseReturnInst();

    BranchInst *parseBranchInst();

    GotoInst *parseGotoInst();

    /**
     * Parses an instruction, consuming its identifier.
     * Invokes the corresponding parser depending on its
     * identifier.
     */
    PartialInst *parseInst();
};
} // namespace ionir
