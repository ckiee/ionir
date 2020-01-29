#include <ionir/construct/expr.h>
#include <ionir/construct/expr/binary_expr.h>
#include <ionir/const/const.h>
#include <ionir/syntax/parser.h>
#include <ionir/syntax/parser_helpers.h>

namespace ionir {
    OptPtr<IdExpr> Parser::parseIdExpr() {
        // TODO

        return std::nullopt;
    }

    OptPtr<Expr<>> Parser::parsePrimaryExpr() {
        TokenKind tokenKind = this->stream.get().getKind();

        return this->makeNotice("Not yet implemented");

        switch (tokenKind) {
            // Identifier expression.
            case TokenKind::Identifier: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

                // TODO: Handle other TokenTypes.
        }

        // At this point, nothing was found.
        return std::nullopt;
    }

    OptPtr<Expr<>> Parser::parseBinaryExprRightSide(Ptr<Expr<>> leftSide, int minimalPrecedence) {
        // If this is a binary operation, find it's precedence.
        while (true) {
            // Capture the current token.
            TokenKind tokenKind = this->stream.get().getKind();

            // Calculate precedence for the current token.
            int firstPrecedence = Const::operatorPrecedence[tokenKind];

            /**
             * If this is a binary operation that binds at least as tightly
             * as the current binary operation, consume it. Otherwise, the process
             * is complete.
             */
            if (firstPrecedence < minimalPrecedence) {
                // TODO: This should throw error? Research.
                return leftSide;
            }

            // At this point, it's a binary operation.
            TokenKind binaryOperatorKind = tokenKind;

            // TODO: Should check if it's a BINARY operator, not just an operator.
            // Ensure the captured operator is validated.
            if (!Classifier::isOperator(binaryOperatorKind)) {
                return this->makeNotice("Expected token to be a binary operator");
            }

            // Skip operator.
            this->stream.skip();

            // Parse the right-side.
            OptPtr<Expr<>> rightSide = this->parsePrimaryExpr();

            IONIR_PARSER_ASSURE(rightSide)

            // Ensure that the right-side was successfully parsed.
            if (!rightSide.has_value()) {
                return this->makeNotice("Unable to parse the right-side of the binary expression");
            }

            // Determine the token precedence of the current token.
            int secondPrecedence = Const::operatorPrecedence[tokenKind];

            /**
             * If binary operator binds less tightly with the right-side than
             * the operator after right-side, let the pending operator take the
             * right-side as its left-side.
             */
            if (firstPrecedence < secondPrecedence) {
                // Invoke the right-side parser.
                rightSide = this->parseBinaryExprRightSide(*rightSide, firstPrecedence + 1);

                // Ensure the right-side was successfully parsed.
                if (rightSide == nullptr) {
                    return this->makeNotice("Unable to parse the right-side of the binary expression");
                }
            }

            BinaryExprOpts opts = BinaryExprOpts{
                binaryOperatorKind,
                firstPrecedence,
                leftSide,
                rightSide,
            };

            // Create the binary expression entity.
            Ptr<BinaryExpr> binaryExpr = std::make_shared<BinaryExpr>(opts);

            // TODO: Set the binaryExpr's name during codegen pass.
            // binaryExpr.SetName("tmp");

            // Merge left-side/right-side.
            leftSide = binaryExpr;
        }
    }
}
