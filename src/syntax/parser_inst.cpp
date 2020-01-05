#include <ionir/construct/expr.h>
#include <ionir/const/const_name.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    std::optional<Ptr<Inst>> Parser::parseInst(Ptr<Section> parent) {
        /**
         * Retrieve the current token's kind to
         * determine the instruction's name &
         * designated parser.
         */
        TokenKind tokenKind = this->stream.get().getKind();

        // Create a buffer instruction to serve as the result.
        std::optional<Ptr<Inst>> inst;

        /**
         * First off, ensure the name is actually
         * registered as an instruction name.
         */
        if (!TokenIdentifier::isInst(tokenKind)) {
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
        this->skipOver(TokenKind::SymbolSemiColon);

        return inst;
    }

    std::optional<Ptr<AllocaInst>> Parser::parseAllocaInst(Ptr<Section> parent) {
        std::optional<std::string> id = this->parseId();

        IONIR_PARSER_ASSURE(id)

        std::optional<Ptr<Type>> type = this->parseType();

        IONIR_PARSER_ASSURE(type)

        return std::make_shared<AllocaInst>(AllocaInstOpts{
            parent,
            *id,
            *type,
        });
    }

    std::optional<Ptr<ReturnInst>> Parser::parseReturnInst(Ptr<Section> parent) {
        // TODO: Return inst does not necessarily take a value. Instead, it should be allowed to return without value, signaling void.
        std::optional<Ptr<Value>> value = this->parseValue();

        IONIR_PARSER_ASSURE(value)

        return std::make_shared<ReturnInst>(ReturnInstOpts{
            parent,
            *value
        });
    }

    std::optional<Ptr<BranchInst>> Parser::parseBranchInst(Ptr<Section> parent) {
        // std::optional<Ptr<Expr>> condition = this->parsePrimaryExpr();

        // // Condition must be set.
        // if (!condition.has_value())
        // {
        //     throw std::runtime_error("Expected branch instruction to have a condition");
        // }

        // // TODO: Use targets.

        // Ptr<Section> body = this->parseSection();
        // std::optional<Ptr<Section>> otherwise = std::nullopt;

        // // Parse the otherwise block if applicable.
        // if (this->is(TokenKind::KeywordElse))
        // {
        //     // Skip over the else keyword.
        //     this->stream.skip();

        //     // Parse the otherwise block.
        //     otherwise = this->parseSection();
        // }

        // return std::make_shared<BranchInst>(BranchInstOpts{
        //     parent,
        //     *condition,
        //     body,
        //     *otherwise,
        // });

        // TODO

        return std::nullopt;
    }

    std::optional<Ptr<CallInst>> Parser::parseCallInst(Ptr<Section> parent) {
        // TODO

        return this->makeNotice("Not yet implemented");
    }
}
