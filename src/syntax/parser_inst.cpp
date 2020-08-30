#include <utility>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Inst> Parser::parseInst(const ionshared::Ptr<BasicBlock> &parent) {
        /**
         * Retrieve the current token's kind to determine the
         * instruction's name & designated parser.
         */
        TokenKind tokenKind = this->tokenStream->get().getKind();

        // Create a buffer instruction to serve as the result.
        AstPtrResult<Inst> inst;

        switch (tokenKind) {
            case TokenKind::InstAlloca: {
                inst = util::castAstPtrResult<AllocaInst, Inst>(
                    this->parseAllocaInst(parent)
                );

                break;
            }

            case TokenKind::InstBranch: {
                inst = util::castAstPtrResult<BranchInst, Inst>(
                    this->parseBranchInst(parent)
                );

                break;
            }

            case TokenKind::InstCall: {
                inst = util::castAstPtrResult<CallInst, Inst>(
                    this->parseCallInst(parent)
                );

                break;
            }

            case TokenKind::InstReturn: {
                inst = util::castAstPtrResult<ReturnInst, Inst>(
                    this->parseReturnInst(parent)
                );

                break;
            }

            case TokenKind::InstStore: {
                inst = util::castAstPtrResult<StoreInst, Inst>(
                    this->parseStoreInst(parent)
                );

                break;
            }

            default: {
                return this->noticeSentinel->makeError<Inst>(
                    IONIR_NOTICE_MISC_UNEXPECTED_TOKEN
                );
            }
        }

        // All instructions should end denoted by a semi-colon.
        IONIR_PARSER_ASSERT(
            this->skipOver(TokenKind::SymbolSemiColon),
            Inst
        );

        return inst;
    }

    AstPtrResult<AllocaInst> Parser::parseAllocaInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstAlloca);

        AstPtrResult<Type> typeResult = this->parseType();

        IONIR_PARSER_ASSERT_RESULT(typeResult, AllocaInst)

        ionshared::Ptr<Type> type = util::getResultValue(typeResult);

        if (type->getTypeKind() == TypeKind::Void) {
            return this->noticeSentinel->makeError<AllocaInst>(IONIR_NOTICE_INST_ALLOCA_VOID);
        }

        return std::make_shared<AllocaInst>(AllocaInstOpts{
            std::move(parent),
            type
        });
    }

    AstPtrResult<ReturnInst> Parser::parseReturnInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstReturn);

        ionshared::Ptr<ReturnInst> returnInst = std::make_shared<ReturnInst>(ReturnInstOpts{
            std::move(parent),

            // Value will be filled in below.
            nullptr
        });

        // TODO: Cannot make error -- it must be std::nullopt. Need a way to handle this with new AstPtrResult<> addition.
        std::optional<AstPtrResult<>> value = std::nullopt;

        /**
         * A non-void value is being returned. Parse a primary expression as the
         * return instruction's value, and if it is a reference, pass in the return
         * instruction to be set as its owner.
         */
        if (!this->is(TokenKind::TypeVoid)) {
            value = this->parsePrimaryExpr(returnInst);
        }
        // Void keyword is being returned, skip over its token.
        else {
            this->skipOver(TokenKind::TypeVoid);
        }

        /**
         * Set the return value if applicable. No need to perform
         * nullptr check as it's underlying value is not a pointer.
         */
        if (value.has_value()) {
            returnInst->setValue(util::getResultValue(*value));
        }

        return returnInst;
    }

    AstPtrResult<BranchInst> Parser::parseBranchInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstBranch);

        // TODO: Not passing any parent to the parser. Should it be this way?
        AstPtrResult<> condition = this->parsePrimaryExpr(nullptr);

        // Condition must be set.
        IONIR_PARSER_ASSERT_RESULT(condition, BranchInst)

        ionshared::Ptr<BranchInst> branchInst = std::make_shared<BranchInst>(BranchInstOpts{
            std::move(parent),
            util::getResultValue(condition),
            nullptr,
            nullptr
        });

        AstPtrResult<Ref<BasicBlock>> bodySection = this->parseRef<BasicBlock>(branchInst);

        IONIR_PARSER_ASSERT_RESULT(bodySection, BranchInst)

        AstPtrResult<Ref<BasicBlock>> otherwiseSection = this->parseRef<BasicBlock>(branchInst);

        IONIR_PARSER_ASSERT_RESULT(otherwiseSection, BranchInst)

        branchInst->setConsequentBlockRef(util::getResultValue(bodySection));
        branchInst->setAlternativeBlockRef(util::getResultValue(otherwiseSection));

        return branchInst;
    }

    AstPtrResult<CallInst> Parser::parseCallInst(const ionshared::Ptr<BasicBlock> &parent) {
        this->skipOver(TokenKind::InstCall);

        std::optional<std::string> calleeId = this->parseId();

        IONIR_PARSER_ASSERT_VALUE(calleeId, CallInst)

        // TODO: Is the BasicBlock parent the correct one? Just passing it because it seems like so. Check.
        ionshared::Ptr<Ref<Function>> callee = std::make_shared<Ref<Function>>(*calleeId, parent);

        return std::make_shared<CallInst>(CallInstOpts{
            parent,
            callee
        });
    }

    AstPtrResult<StoreInst> Parser::parseStoreInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstStore);

        AstPtrResult<Value<>> value = this->parseValue();

        IONIR_PARSER_ASSERT_RESULT(value, StoreInst)

        ionshared::Ptr<StoreInst> storeInst = std::make_shared<StoreInst>(StoreInstOpts{
            std::move(parent),
            util::getResultValue(value),

            // The target reference will be filled below.
            nullptr
        });

        AstPtrResult<Ref<AllocaInst>> target = this->parseRef<AllocaInst>(storeInst);

        // TODO: StoreInst?
        IONIR_PARSER_ASSERT_RESULT(target, StoreInst)

        // Fill the target reference in the store instruction.
        storeInst->setTarget(util::getResultValue(target));

        return storeInst;
    }

    AstPtrResult<JumpInst> Parser::parseJumpInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstJump);

        ionshared::Ptr<JumpInst> jumpInst = std::make_shared<JumpInst>(JumpInstOpts{
            std::move(parent),

            // The basic block reference will be filled below.
            nullptr
        });

        AstPtrResult<Ref<BasicBlock>> target = this->parseRef<BasicBlock>(jumpInst);

        IONIR_PARSER_ASSERT_RESULT(target, JumpInst)

        // Fill the basic block reference in the jump instruction.
        jumpInst->setBlockRef(util::getResultValue(target));

        return jumpInst;
    }
}
