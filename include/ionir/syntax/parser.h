#pragma once

#include <optional>
#include <string>
#include <ionshared/error_handling/notice_factory.h>
#include <ionir/error_handling/notice_sentinel.h>
#include <ionir/construct/value/integer_literal.h>
#include <ionir/construct/value/char_literal.h>
#include <ionir/construct/value/string_literal.h>
#include <ionir/construct/inst.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/inst/store.h>
#include <ionir/construct/inst/jump.h>
#include <ionir/construct/pseudo/directive.h>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/classifier.h>
#include <ionir/construct/extern.h>
#include <ionir/construct/function.h>
#include <ionir/construct/global.h>
#include <ionir/construct/pseudo/args.h>
#include <ionir/construct/prototype.h>
#include <ionir/construct/function_body.h>
#include <ionir/construct/basic_block.h>
#include <ionir/construct/module.h>
#include <ionir/construct/register_assign.h>
#include <ionir/misc/helpers.h>
#include <ionir/const/const_name.h>
#include <ionir/const/notice.h>
#include "ast_result.h"
#include "parser_helpers.h"

namespace ionir {
    class Parser {
    private:
        ionshared::Ptr<TokenStream> tokenStream;

        ionshared::Ptr<ionshared::NoticeStack> noticeStack;

        ionshared::Ptr<NoticeSentinel> noticeSentinel;

        std::string filePath;

        Classifier classifier;

    protected:
        [[nodiscard]] Classifier getClassifier() const noexcept;

        [[nodiscard]] bool is(TokenKind tokenKind) noexcept;

        [[nodiscard]] bool isNext(TokenKind tokenKind);

        bool expect(TokenKind tokenKind);

        bool skipOver(TokenKind tokenKind);

        [[nodiscard]] ionshared::NoticeFactory createNoticeFactory() noexcept;

        std::nullopt_t makeNotice(
            std::string message,
            ionshared::NoticeType type = ionshared::NoticeType::Error
        );

    public:
        explicit Parser(
            ionshared::Ptr<TokenStream> tokenStream,

            const ionshared::Ptr<ionshared::NoticeStack> &noticeStack =
                std::make_shared<ionshared::Stack<ionshared::Notice>>(),

            std::string filePath = ConstName::anonymous
        );

        [[nodiscard]] ionshared::Ptr<TokenStream> getTokenStream() const noexcept;

        [[nodiscard]] ionshared::Ptr<ionshared::NoticeStack> getNoticeStack() const noexcept;

        [[nodiscard]] std::string getFilePath() const noexcept;

        AstPtrResult<> parseTopLevel(const ionshared::Ptr<Module> &parent);

        /**
         * Parses a integer literal in the form of long (or integer 64).
         */
        AstPtrResult<IntegerLiteral> parseIntegerLiteral();

        AstPtrResult<CharLiteral> parseCharLiteral();

        AstPtrResult<StringLiteral> parseStringLiteral();

        std::optional<std::string> parseId();

        AstPtrResult<Type> parseType();

        AstPtrResult<Type> parseTypePrefix();

        AstPtrResult<VoidType> parseVoidType();

        AstPtrResult<IntegerType> parseIntegerType();

        AstResult<Arg> parseArg();

        AstPtrResult<Args> parseArgs();

        AstPtrResult<Prototype> parsePrototype(const ionshared::Ptr<Module> &parent);

        AstPtrResult<Extern> parseExtern(const ionshared::Ptr<Module> &parent);

        AstPtrResult<Function> parseFunction(const ionshared::Ptr<Module> &parent);

        AstPtrResult<Global> parseGlobal();

        AstPtrResult<Value<>> parseValue();

        AstPtrResult<> parsePrimaryExpr(const ionshared::Ptr<Construct> &parent);

        AstPtrResult<BasicBlock> parseBasicBlock(ionshared::Ptr<FunctionBody> parent);

        AstPtrResult<FunctionBody> parseFunctionBody(const ionshared::Ptr<Function> &parent);

        AstPtrResult<AllocaInst> parseAllocaInst(ionshared::Ptr<BasicBlock> parent);

        AstPtrResult<ReturnInst> parseReturnInst(ionshared::Ptr<BasicBlock> parent);

        AstPtrResult<BranchInst> parseBranchInst(ionshared::Ptr<BasicBlock> parent);

        AstPtrResult<CallInst> parseCallInst(const ionshared::Ptr<BasicBlock> &parent);

        AstPtrResult<StoreInst> parseStoreInst(ionshared::Ptr<BasicBlock> parent);

        AstPtrResult<JumpInst> parseJumpInst(ionshared::Ptr<BasicBlock> parent);

        /**
         * Parses an instruction, consuming its identifier. Invokes the corresponding
         * parser depending on its identifier.
         */
        AstPtrResult<Inst> parseInst(const ionshared::Ptr<BasicBlock> &parent);

        AstPtrResult<Module> parseModule();

        AstPtrResult<RegisterAssign> parseRegisterAssign(const ionshared::Ptr<BasicBlock> &parent);

        std::optional<std::string> parseLine();

        // TODO: Add comment-parsing support.

        std::optional<Directive> parseDirective();

        template<typename T = Construct>
        AstPtrResult<Ref<T>> parseRef(ionshared::Ptr<Construct> owner) {
            std::optional<std::string> id = this->parseId();

            IONIR_PARSER_ASSERT_VALUE(id, Ref<T>)

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
