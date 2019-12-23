#include <optional>
#include "misc/stack.h"
#include "token_const.h"
#include "const.h"

namespace ionir
{
Map<IntegerKind, LlvmIntTypeResolver> Const::integerTypeResolverMap = {};

const std::string Const::sectionInternalPrefix = ".";

std::map<TokenType, int> Const::operatorPrecedence = {
    {TokenType::OperatorAdd, 20},
    {TokenType::OperatorSub, 20},
    {TokenType::OperatorMultiply, 40},
    {TokenType::OperatorDivide, 40},
    {TokenType::OperatorModulo, 40},
    {TokenType::OperatorExponent, 80},
};

const std::string Const::sectionEntryId = Const::sectionInternalPrefix + "entry";

// TODO: Refactor.
// Const::Const()
// {
//     // Register integer kind -> integer type resolvers.
//     auto map = this->integerTypeResolverMap.unwrap();

//     // TODO: Fix insertion error.
//     // map.insert(IntegerKind::Int1, &llvm::IntegerType::getInt1Ty);
//     // map.insert(IntegerKind::Int32, &llvm::IntegerType::getInt32Ty);
//     // map.insert(IntegerKind::Int64, &llvm::IntegerType::getInt64Ty);
//     // map.insert(IntegerKind::Int128, &llvm::IntegerType::getInt128Ty);
// }

std::optional<LlvmIntTypeResolver> Const::tryGetIntTypeResolver(IntegerKind kind)
{
    return Const::integerTypeResolverMap.tryGet(kind);
}

std::string Const::idFoobar = "foobar";

bool Const::init()
{
    if (!TokenConst::getIsInitialized())
    {
        return false;
    }

    Stack<std::optional<std::string>> valueStack = {};

    valueStack.push(TokenConst::findSimpleValue(TokenType::KeywordVoid));
    valueStack.push(TokenConst::findSimpleValue(TokenType::KeywordString));
    valueStack.push(TokenConst::findSimpleValue(TokenType::KeywordInt));

    // TODO: Make Stack iterable.
//    for (const auto value : valueStack.unwrap())
//    {
//        if (!value.has_value())
//        {
//            throw std::runtime_error("Unable to find corresponding value");
//        }
//    }

    Const::typeInt = *valueStack.pop();
    Const::typeString = *valueStack.pop();
    Const::typeVoid = *valueStack.pop();

    return true;
}
} // namespace ionir
