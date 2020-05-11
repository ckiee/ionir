#include <ionir/const/token_const.h>

namespace ionir {
    BiMap<std::string, TokenKind> TokenConst::operators = BiMap<std::string, TokenKind>(std::map<std::string, TokenKind>{
        {"+", TokenKind::OperatorAdd},
        {"-", TokenKind::OperatorSub},
        {"*", TokenKind::OperatorMultiply},
        {"/", TokenKind::OperatorDivide},
        {"%", TokenKind::OperatorModulo},
        {"^", TokenKind::OperatorExponent},
        {">", TokenKind::OperatorGreaterThan},
        {"<", TokenKind::OperatorLessThan}
    });
}
