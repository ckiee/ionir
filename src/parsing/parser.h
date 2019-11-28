#pragma once

#include <optional>
#include <string>
#include "syntax/token.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/args.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"
#include "ast_nodes/inst.h"
#include "misc/notice.h"
#include "misc/notice_context.h"
#include "misc/notice_type.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/return.h"
#include "ast_nodes/insts/branch.h"

namespace ionir
{
class Parser
{
protected:
    TokenStream stream;

    std::vector<Notice> notices;

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
    LiteralInt *parseInt();

    LiteralChar *parseChar();

    StringValue *parseString();

    std::string parseIdentifier();

    Type *parseType();

    Arg parseArg();

    Args parseArgs();

    Prototype *parsePrototype();

    Extern *parseExtern();

    Block *parseBlock();

    Value *parseValue();

    std::optional<Node *> parsePrimaryExpr();

    Node *parseBinaryExprRightSide(Node *leftSide, int minimalPrecedence);

    AllocaInst *parseAllocaInst();

    ReturnInst *parseReturnInst();

    BranchInst *parseBranchInst();

    /**
     * Parses an instruction, consuming its identifier.
     * Invokes the corresponding parser depending on its
     * identifier.
     */
    Inst *parseInst();
};
} // namespace ionir
