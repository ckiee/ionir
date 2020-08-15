#include <utility>
#include <ionir/syntax/parser.h>

namespace ionir {
    ionshared::OptPtr<Inst> Parser::parseInst(const ionshared::Ptr<BasicBlock> &parent) {
        /**
         * Retrieve the current token's kind to
         * determine the instruction's name &
         * designated parser.
         */
        TokenKind tokenKind = this->stream.get().getKind();

        // Create a buffer instruction to serve as the result.
        ionshared::OptPtr<Inst> inst;

        /**
         * First off, ensure the name is actually
         * registered as an instruction name.
         */
        if (!Classifier::isInst(tokenKind)) {
            return std::nullopt;
        }

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
                return this->makeNotice("Unrecognized instruction name");
            }
        }

        // All instructions should end denoted by a semi-colon.
        IONIR_PARSER_ASSERT(this->skipOver(TokenKind::SymbolSemiColon))

        return inst;
    }

    ionshared::OptPtr<AllocaInst> Parser::parseAllocaInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstAlloca);

        ionshared::OptPtr<Type> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        if (type->get()->getTypeKind() == TypeKind::Void) {
            return this->makeNotice("Cannot allocate void type");
        }

        return std::make_shared<AllocaInst>(AllocaInstOpts{
            std::move(parent),
            *type,
        });
    }

    ionshared::OptPtr<ReturnInst> Parser::parseReturnInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstReturn);

        ionshared::Ptr<ReturnInst> returnInst = std::make_shared<ReturnInst>(ReturnInstOpts{
            std::move(parent),
            nullptr
        });

        ionshared::OptPtr<Construct> value = std::nullopt;

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

    ionshared::OptPtr<BranchInst> Parser::parseBranchInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstBranch);

        // TODO: Not passing any parent to the parser. Should it be this way?
        ionshared::OptPtr<Construct> condition = this->parsePrimaryExpr(nullptr);

        // Condition must be set.
        IONIR_PARSER_ASSURE(condition)

        ionshared::Ptr<BranchInst> branchInst = std::make_shared<BranchInst>(BranchInstOpts{
            std::move(parent),
            *condition,
            nullptr,
            nullptr
        });

        ionshared::OptPtr<Ref<BasicBlock>> bodySection = this->parseRef<BasicBlock>(branchInst);

        IONIR_PARSER_ASSURE(bodySection)

        ionshared::OptPtr<Ref<BasicBlock>> otherwiseSection = this->parseRef<BasicBlock>(branchInst);

        IONIR_PARSER_ASSURE(otherwiseSection)

        branchInst->setBlockRef(*bodySection);
        branchInst->setOtherwiseBlockRef(*otherwiseSection);

        return branchInst;
    }

    ionshared::OptPtr<CallInst> Parser::parseCallInst(const ionshared::Ptr<BasicBlock> &parent) {
        this->skipOver(TokenKind::InstCall);

        std::optional<std::string> calleeId = this->parseId();

        IONIR_PARSER_ASSURE(calleeId)

        // TODO: Is the BasicBlock parent the correct one? Just passing it because it seems like so. Check.
        ionshared::Ptr<Ref<Function>> callee = std::make_shared<Ref<Function>>(*calleeId, parent);

        return std::make_shared<CallInst>(CallInstOpts{
            parent,
            callee
        });;
    }

    ionshared::OptPtr<StoreInst> Parser::parseStoreInst(ionshared::Ptr<BasicBlock> parent) {
        this->skipOver(TokenKind::InstStore);

        ionshared::OptPtr<Value<>> value = this->parseValue();

        IONIR_PARSER_ASSURE(value)

        ionshared::Ptr<StoreInst> storeInst = std::make_shared<StoreInst>(StoreInstOpts{
            std::move(parent),
            *value,
            nullptr
        });

        ionshared::OptPtr<Ref<AllocaInst>> target = this->parseRef<AllocaInst>(storeInst);

        IONIR_PARSER_ASSURE(target)

        storeInst->setTarget(*target);

        return storeInst;
    }
}
