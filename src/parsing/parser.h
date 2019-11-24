#pragma once

#include <limits>
#include <string>
#include <utility>
#include "syntax/token.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/args.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"
#include "ast_nodes/inst.h"
#include "misc/notice.h"
#include "misc/notice_context.h"
#include "misc/notice_type.h"

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

    std::string parseIdentifier();

    Type *parseType();

    Arg parseArg();

    Args parseArgs();

    Prototype *parsePrototype();

    Extern *parseExtern();

    Block *parseBlock();

    Value *parseValue();

    Inst *parseInst();
};
} // namespace ionir
