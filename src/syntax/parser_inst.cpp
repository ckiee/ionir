#include <utility>
#include <ionir/const/notice.h>
#include <ionir/syntax/parser.h>

namespace ionir {
    AstPtrResult<Inst> Parser::parseInst(const ionshared::Ptr<BasicBlock> &parent) {
        /**
         * Retrieve the current token's kind to determine the
         * instruction's name & designated parser.
         */
        TokenKind tokenKind = this->stream.get().getKind();

        // Create a buffer instruction to serve as the result.
        AstPtrResult<Inst> inst;

        switch (tokenKind) {
            case TokenKind::InstAlloca: {
                inst = this->parseAllocaInst(parent);

                break;
            }

            case TokenKind::InstBranch: {
                inst = this->parseBranchInst(parent);

                break;
            }

            case TokenKind::InstCall: {
                inst = this->parseCallInst(parent);

                break;
            }

            case TokenKind::InstReturn: {
                inst = this->parseReturnInst(parent);

                break;
            }

            case TokenKind::InstStore: {
                inst = this->parseStoreInst(parent);

                break;
            }

            default: {
                return this->noticeSentinel->makeError<Inst>(IONIR_NOTICE_MISC_UNEXPECTED_TOKEN);
            }
        }

        // All instructions should end denoted by a semi-colon.
        this->assertOrError(this->skipOver(TokenKind::SymbolSemiColon));

        return inst;
    }

    AstPtrResult<AllocaInst> Parser::parseAllocaInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstAlloca);

        AstPtrResult<Type> typeResult = this->parseType();

        this->assertHasValue(typeResult);

        ionshared::Ptr<Type> type = Util::getResultPtrValue(typeResult);

        if (type->getTypeKind() == TypeKind::Void) {
            return this->noticeSentinel->makeError<AllocaInst>(IONIR_NOTICE_INST_CANNOT_ALLOCATE_VOID);
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
            nullptr
        });

        // TODO: Cannot make error -- it must be std::nullopt. Need a way to handle this with new AstPtrResult<> addition.
        AstPtrResult<> value = std::nullopt;

        /**
         * A non-void value is being returned. Parse a primary
         * expression as the return instruction's value, and if
         * it is a reference, pass in the return instruction to
         * be set as its owner.
         */
        if (!this->is(TokenKind::TypeVoid)) {
            value = this->parsePrimaryExpr(returnInst);
        }
        /**
         * Void keyword is being returned, skip over its token.
         */
        else {
            this->skipOver(TokenKind::TypeVoid);
        }

        returnInst->setValue(value);

        return returnInst;
    }

    AstPtrResult<BranchInst> Parser::parseBranchInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstBranch);

        // TODO: Not passing any parent to the parser. Should it be this way?
        AstPtrResult<> condition = this->parsePrimaryExpr(nullptr);

        // Condition must be set.
        this->assertHasValue(condition);

        ionshared::Ptr<BranchInst> branchInst = std::make_shared<BranchInst>(BranchInstOpts{
            std::move(parent),
            Util::getResultPtrValue(condition),
            nullptr,
            nullptr
        });

        AstPtrResult<Ref<BasicBlock>> bodySection = this->parseRef<BasicBlock>(branchInst);

        this->assertHasValue(bodySection);

        AstPtrResult<Ref<BasicBlock>> otherwiseSection = this->parseRef<BasicBlock>(branchInst);

        this->assertHasValue(otherwiseSection);

        branchInst->setBlockRef(Util::getResultPtrValue(bodySection));
        branchInst->setOtherwiseBlockRef(Util::getResultPtrValue(otherwiseSection));

        return branchInst;
    }

    AstPtrResult<CallInst> Parser::parseCallInst(const ionshared::Ptr<BasicBlock> &parent) {
        this->skipOver(TokenKind::InstCall);

        std::optional<std::string> calleeId = this->parseId();

        this->assertHasValue(calleeId);

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

        this->assertHasValue(value);

        ionshared::Ptr<StoreInst> storeInst = std::make_shared<StoreInst>(StoreInstOpts{
            std::move(parent),
            Util::getResultPtrValue(value),
            nullptr
        });

        AstPtrResult<Ref<AllocaInst>> target = this->parseRef<AllocaInst>(storeInst);

        this->assertHasValue(target);

        storeInst->setTarget(Util::getResultPtrValue(target));

        return storeInst;
    }
}
