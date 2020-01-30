#include <ionir/const/token_const.h>

namespace ionir {
    TokenKindMap TokenConst::operators = {
        {"+", TokenKind::OperatorAdd},
        {"-", TokenKind::OperatorSub},
        {"*", TokenKind::OperatorMultiply},
        {"/", TokenKind::OperatorDivide},
        {"%", TokenKind::OperatorModulo},
        {"^", TokenKind::OperatorExponent},
        {">", TokenKind::OperatorGreaterThan},
        {"<", TokenKind::OperatorLessThan}
    };
}
