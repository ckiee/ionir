#pragma once

#include <optional>
#include <string>
#include <ionshared/error_handling/notice_factory.h>
#include <ionir/construct/value/integer_value.h>
#include <ionir/construct/value/char_value.h>
#include <ionir/construct/value/string_value.h>
#include <ionir/construct/inst.h>
#include <ionir/construct/inst/alloca.h>
#include <ionir/construct/inst/return.h>
#include <ionir/construct/inst/branch.h>
#include <ionir/construct/inst/call.h>
#include <ionir/construct/inst/store.h>
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
#include "scope.h"
#include "parser_helpers.h"
#include "ast_result.h"

namespace ionir {
    class Parser {
    private:
        TokenStream stream;

        ionshared::Ptr<ionshared::NoticeStack> noticeStack;

        std::string filePath;

        Classifier classifier;

    protected:
        [[nodiscard]] Classifier getClassifier() const noexcept;

        bool is(TokenKind tokenKind) noexcept;

        bool isNext(TokenKind tokenKind);

        bool expect(TokenKind tokenKind);

        bool skipOver(TokenKind tokenKind);

        ionshared::NoticeFactory createNoticeFactory() noexcept;

        std::nullopt_t makeNotice(std::string message, ionshared::NoticeType type = ionshared::NoticeType::Error);

    public:
        explicit Parser(
            TokenStream stream,

            ionshared::Ptr<ionshared::NoticeStack> noticeStack =
                std::make_shared<ionshared::Stack<ionshared::Notice>>(),

            std::string filePath = ConstName::anonymous
        );

        [[nodiscard]] ionshared::Ptr<ionshared::NoticeStack> getNoticeStack() const;

        [[nodiscard]] std::string getFilePath() const;

        AstPtrResult<Construct> parseTopLevel(const ionshared::Ptr<Module> &parent);

        /**
         * Parses a integer literal in the form of long (or integer 64).
         */
        ionshared::OptPtr<IntegerValue> parseInt();

        ionshared::OptPtr<CharValue> parseChar();

        ionshared::OptPtr<StringValue> parseString();

        std::optional<std::string> parseId();

        ionshared::OptPtr<Type> parseType();

        ionshared::OptPtr<Type> parseTypePrefix();

        ionshared::OptPtr<VoidType> parseVoidType();

        ionshared::OptPtr<IntegerType> parseIntegerType();

        std::optional<Arg> parseArg();

        ionshared::OptPtr<Args> parseArgs();

        ionshared::OptPtr<Prototype> parsePrototype(const ionshared::Ptr<Module> &parent);

        ionshared::OptPtr<Extern> parseExtern(const ionshared::Ptr<Module> &parent);

        ionshared::OptPtr<Function> parseFunction(const ionshared::Ptr<Module> &parent);

        ionshared::OptPtr<Global> parseGlobal();

        ionshared::OptPtr<Value<>> parseValue();

        ionshared::OptPtr<Construct> parsePrimaryExpr(ionshared::Ptr<Construct> parent);

        ionshared::OptPtr<BasicBlock> parseBasicBlock(ionshared::Ptr<FunctionBody> parent);

        ionshared::OptPtr<FunctionBody> parseFunctionBody(const ionshared::Ptr<Function> &parent);

        ionshared::OptPtr<AllocaInst> parseAllocaInst(ionshared::Ptr<BasicBlock> parent);

        ionshared::OptPtr<ReturnInst> parseReturnInst(ionshared::Ptr<BasicBlock> parent);

        ionshared::OptPtr<BranchInst> parseBranchInst(ionshared::Ptr<BasicBlock> parent);

        ionshared::OptPtr<CallInst> parseCallInst(const ionshared::Ptr<BasicBlock> &parent);

        ionshared::OptPtr<StoreInst> parseStoreInst(ionshared::Ptr<BasicBlock> parent);

        /**
         * Parses an instruction, consuming its identifier. Invokes the corresponding
         * parser depending on its identifier.
         */
        ionshared::OptPtr<Inst> parseInst(const ionshared::Ptr<BasicBlock> &parent);

        ionshared::OptPtr<Module> parseModule();

        ionshared::OptPtr<RegisterAssign> parseRegisterAssign(const ionshared::Ptr<BasicBlock> &parent);

        std::optional<std::string> parseLine();

        // TODO: Add comment-parsing support.

        std::optional<Directive> parseDirective();

        template<typename T = Construct>
        ionshared::OptPtr<Ref<T>> parseRef(ionshared::Ptr<Construct> owner) {
            std::optional<std::string> id = this->parseId();

            IONIR_PARSER_ASSURE(id)

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
