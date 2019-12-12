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
    TokenStream *stream;

    std::vector<Notice> notices;

    TokenIdentifier tokenIdentifier;

    bool withinRange(long value, long from, long to);

    bool is(TokenType type);

    void expect(TokenType type);

    void skipOver(TokenType type);

    NoticeContext createNoticeContext();

    Notice createNotice(NoticeType type, std::string message);

    std::shared_ptr<Scope> createScope();

    void pushNotice(NoticeType type, std::string message);

public:
    Parser(TokenStream *stream);

    std::vector<Notice> getNotices() const;

    /**
     * Parses a integer literal in the form of
     * long (or integer 64).
     */
    std::shared_ptr<IntValue> parseInt();

    std::shared_ptr<CharValue> parseChar();

    std::shared_ptr<StringValue> parseString();

    std::string parseId();

    std::shared_ptr<Type> parseType();

    Arg parseArg();

    std::shared_ptr<Args> parseArgs();

    std::shared_ptr<Prototype> parsePrototype();

    std::shared_ptr<Extern> parseExtern();

    std::shared_ptr<Function> parseFunction();

    std::shared_ptr<Value> parseValue();

    std::optional<std::shared_ptr<Node>> parsePrimaryExpr();

    std::shared_ptr<Node> parseBinaryExprRightSide(std::shared_ptr<Node> leftSide, int minimalPrecedence);

    std::shared_ptr<Section> parseSection();

    std::shared_ptr<Block> parseBlock();

    std::shared_ptr<AllocaInst> parseAllocaInst();

    std::shared_ptr<ReturnInst> parseReturnInst();

    std::shared_ptr<BranchInst> parseBranchInst();

    std::shared_ptr<GotoInst> parseGotoInst();

    /**
     * Parses an instruction, consuming its identifier.
     * Invokes the corresponding parser depending on its
     * identifier.
     */
    std::shared_ptr<Inst> parseInst();
};
} // namespace ionir
