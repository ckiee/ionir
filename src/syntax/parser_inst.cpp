#include <ionir/construct/expr.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    OptPtr<Inst> Parser::parseInst(Ptr<Section> parent) {
        /**
         * Retrieve the current token's kind to
         * determine the instruction's name &
         * designated parser.
         */
        TokenKind tokenKind = this->stream.get().getKind();

        // Create a buffer instruction to serve as the result.
        OptPtr<Inst> inst;

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

    OptPtr<AllocaInst> Parser::parseAllocaInst(Ptr<Section> parent) {
        this->skipOver(TokenKind::InstAlloca);

        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        OptPtr<Type> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        return std::make_shared<AllocaInst>(AllocaInstOpts{
            parent,
            *id,
            *type,
        });
    }

    OptPtr<ReturnInst> Parser::parseReturnInst(Ptr<Section> parent) {
        this->skipOver(TokenKind::InstReturn);

        OptPtr<Value<>> value = std::nullopt;

        /**
         * A non-void value is being returned.
         */
        if (!this->is(TokenKind::TypeVoid)) {
            value = this->parseValue();
        }
        /**
         * Void keyword is being returned, skip over its token.
         */
        else {
            this->skipOver(TokenKind::TypeVoid);
        }

        return std::make_shared<ReturnInst>(ReturnInstOpts{
            parent,
            value
        });
    }

    OptPtr<BranchInst> Parser::parseBranchInst(Ptr<Section> parent) {
        this->skipOver(TokenKind::InstBranch);

        OptPtr<Expr<>> condition = this->parsePrimaryExpr();

        // Condition must be set.
        IONIR_PARSER_ASSURE(condition)

        Ptr<BranchInst> branchInst = std::make_shared<BranchInst>(BranchInstOpts{
            parent,
            *condition,
            nullptr,
            nullptr
        });

        OptPtr<Ref<Section>> bodySection = this->parseRef<Section>(branchInst);

        IONIR_PARSER_ASSURE(bodySection)

        OptPtr<Ref<Section>> otherwiseSection = this->parseRef<Section>(branchInst);

        IONIR_PARSER_ASSURE(otherwiseSection)

        branchInst->setBodyRef(*bodySection);
        branchInst->setOtherwiseRef(*otherwiseSection);

        return branchInst;
    }

    OptPtr<CallInst> Parser::parseCallInst(Ptr<Section> parent) {
        this->skipOver(TokenKind::InstCall);

        // TODO

        return this->makeNotice("Not yet implemented");
    }

    OptPtr<StoreInst> Parser::parseStoreInst(Ptr<Section> parent) {
        this->skipOver(TokenKind::InstStore);

        OptPtr<Value<>> value = this->parseValue();

        IONIR_PARSER_ASSURE(value)

        Ptr<StoreInst> storeInst = std::make_shared<StoreInst>(StoreInstOpts{
            parent,
            *value,
            nullptr
        });

        OptPtr<Ref<AllocaInst>> target = this->parseRef<AllocaInst>(storeInst);

        IONIR_PARSER_ASSURE(target)

        storeInst->setTarget(*target);

        return storeInst;
    }
}
