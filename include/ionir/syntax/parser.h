#pragma once

#include <optional>
#include <string>
#include <ionir/construct/expr.h>
#include <ionir/construct/expr/id.h>
#include <ionir/construct/value/integer.h>
#include <ionir/construct/value/char.h>
#include <ionir/construct/value/string.h>
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
#include <ionir/reporting/notice_factory.h>
#include <ionir/misc/helpers.h>
#include <ionir/const/const_name.h>
#include "scope.h"
#include "parser_helpers.h"

namespace ionir {
    class Parser {
    private:
        TokenStream stream;

        StackTrace stackTrace;

        std::string filePath;

        Classifier classifier;

    protected:
        Classifier getClassifier() const noexcept;

        bool is(TokenKind tokenKind) noexcept;

        bool isPeek(TokenKind tokenKind);

        bool expect(TokenKind tokenKind);

        bool skipOver(TokenKind tokenKind);

        NoticeFactory createNoticeFactory() noexcept;

        std::nullopt_t makeNotice(std::string message, NoticeType type = NoticeType::Error);

    public:
        explicit Parser(TokenStream stream, StackTrace stackTrace = {},
            std::string filePath = ConstName::anonymous);

        StackTrace getStackTrace() const;

        std::string getFilePath() const;

        OptPtr<Construct> parseTopLevel();

        /**
         * Parses a integer literal in the form of
         * long (or integer 64).
         */
        OptPtr<IntegerValue> parseInt();

        OptPtr<CharValue> parseChar();

        OptPtr<StringValue> parseString();

        std::optional<std::string> parseId();

        OptPtr<Type> parseType();

        OptPtr<Type> parseTypePrefix();

        OptPtr<VoidType> parseVoidType();

        OptPtr<IntegerType> parseIntegerType();

        std::optional<Arg> parseArg();

        OptPtr<Args> parseArgs();

        OptPtr<Prototype> parsePrototype();

        OptPtr<Extern> parseExtern();

        OptPtr<Function> parseFunction();

        OptPtr<Global> parseGlobal();

        OptPtr<Value<>> parseValue();

        OptPtr<IdExpr> parseIdExpr();

        OptPtr<Expr<>> parsePrimaryExpr();

        OptPtr<Expr<>> parseBinaryExprRightSide(Ptr<Expr<>> leftSide, int minimalPrecedence);

        OptPtr<BasicBlock> parseSection(Ptr<FunctionBody> parent);

        OptPtr<FunctionBody> parseFunctionBody(Ptr<Function> parent);

        OptPtr<AllocaInst> parseAllocaInst(Ptr<BasicBlock> parent);

        OptPtr<ReturnInst> parseReturnInst(Ptr<BasicBlock> parent);

        OptPtr<BranchInst> parseBranchInst(Ptr<BasicBlock> parent);

        OptPtr<CallInst> parseCallInst(Ptr<BasicBlock> parent);

        OptPtr<StoreInst> parseStoreInst(Ptr<BasicBlock> parent);

        /**
         * Parses an instruction, consuming its identifier.
         * Invokes the corresponding parser depending on its
         * identifier.
         */
        OptPtr<Inst> parseInst(Ptr<BasicBlock> parent);

        OptPtr<Module> parseModule();

        std::optional<std::string> parseLine();

        // TODO: Add comment-parsing support.

        std::optional<Directive> parseDirective();

        template<typename T = Construct>
        OptPtr<Ref<T>> parseRef(Ptr<Construct> owner) {
            std::optional<std::string> id = this->parseId();

            IONIR_PARSER_ASSURE(id)

            return std::make_shared<Ref<T>>(*id, owner);
        }
    };
}
