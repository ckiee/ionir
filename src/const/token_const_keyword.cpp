#include <ionir/const/const_name.h>
#include <ionir/const/token_const.h>

namespace ionir {
    TokenKindMap TokenConst::keywords = {
        {ConstName::instCall, TokenKind::InstCall},
        {ConstName::instStore, TokenKind::InstStore},
        {ConstName::instReturn, TokenKind::InstReturn},
        {ConstName::instAlloca, TokenKind::InstAlloca},
        {ConstName::instBranch, TokenKind::InstBranch},
        {"fn", TokenKind::KeywordFunction},
        {"module", TokenKind::KeywordModule},
        {"extern", TokenKind::KeywordExtern},
        {"global", TokenKind::KeywordGlobal},
        {"else", TokenKind::KeywordElse},
        {"mut", TokenKind::KeywordMutable},
        {ConstName::typeVoid, TokenKind::TypeVoid},
        {ConstName::typeBool, TokenKind::TypeBool},
        {ConstName::typeInt16, TokenKind::TypeInt16},
        {ConstName::typeInt32, TokenKind::TypeInt32},
        {ConstName::typeInt64, TokenKind::TypeInt64},
        {ConstName::typeUnsignedInt16, TokenKind::TypeUnsignedInt16},
        {ConstName::typeUnsignedInt32, TokenKind::TypeUnsignedInt32},
        {ConstName::typeUnsignedInt64, TokenKind::TypeUnsignedInt64},
        {ConstName::typeFloat16, TokenKind::TypeFloat16},
        {ConstName::typeFloat32, TokenKind::TypeFloat32},
        {ConstName::typeFloat64, TokenKind::TypeFloat64},
        {ConstName::typeChar, TokenKind::TypeChar},
        {ConstName::typeString, TokenKind::TypeString}
    };
}
