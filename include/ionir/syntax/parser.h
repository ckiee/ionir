#pragma once

#include <optional>
#include <string>
#include <ionshared/error_handling/notice_factory.h>
#include <ionir/error_handling/notice_sentinel.h>
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
#include <ionir/const/notice.h>
#include "scope.h"
#include "ast_result.h"

namespace ionir {
    class Parser {
    private:
        TokenStream stream;

        ionshared::Ptr<ionshared::NoticeStack> noticeStack;

        ionshared::Ptr<NoticeSentinel> noticeSentinel;

        std::string filePath;

        Classifier classifier;

    protected:
        template<typename T = Construct>
        inline AstPtrResult<T> assertOrError(bool expression) {
            if (!expression) {
                return this->makeNotice(IONIR_NOTICE_MISC_ASSERTION_FAILED);
            }
        }

        template<typename TVariable, typename TConstruct = Construct>
        inline AstPtrResult<TConstruct> assertHasValue(std::optional<TVariable> variable) {
            return this->assertOrError<TConstruct>(ionshared::Util::hasValue(variable));
        }

        template<typename T = Construct>
        inline AstPtrResult<T> assertHasValue(AstPtrResult<T> result) {
            return this->assertOrError<T>(Util::hasValue(result));
        }

        template<typename T = Construct>
        inline AstPtrResult<T> assertTokenKind(TokenKind tokenKind) {
            return this->assertOrError<T>(this->is(tokenKind));
        }

        [[nodiscard]] Classifier getClassifier() const noexcept;

        [[nodiscard]] bool is(TokenKind tokenKind) noexcept;

        [[nodiscard]] bool isNext(TokenKind tokenKind);

        bool expect(TokenKind tokenKind);

        bool skipOver(TokenKind tokenKind);

        ionshared::NoticeFactory createNoticeFactory() noexcept;

        std::nullopt_t makeNotice(
            std::string message,
            ionshared::NoticeType type = ionshared::NoticeType::Error
        );

    public:
        explicit Parser(
            TokenStream stream,

            const ionshared::Ptr<ionshared::NoticeStack> &noticeStack =
                std::make_shared<ionshared::Stack<ionshared::Notice>>(),

            std::string filePath = ConstName::anonymous
        );

        [[nodiscard]] ionshared::Ptr<ionshared::NoticeStack> getNoticeStack() const;

        [[nodiscard]] std::string getFilePath() const;

        AstPtrResult<> parseTopLevel(const ionshared::Ptr<Module> &parent);

        /**
         * Parses a integer literal in the form of long (or integer 64).
         */
        AstPtrResult<IntegerValue> parseInt();

        AstPtrResult<CharValue> parseChar();

        AstPtrResult<StringValue> parseString();

        std::optional<std::string> parseId();

        AstPtrResult<Type> parseType();

        AstPtrResult<Type> parseTypePrefix();

        AstPtrResult<VoidType> parseVoidType();

        AstPtrResult<IntegerType> parseIntegerType();

        std::optional<Arg> parseArg();

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

            this->assertHasValue(id);

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
