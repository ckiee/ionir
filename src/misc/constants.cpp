#include "constants.h"

namespace ionir
{
const std::string Const::sectionInternalPrefix = ".";

const std::map<TokenType, int> Const::tokenPrecedence = {
    {TokenType::OperatorAdd, 20},
    {TokenType::OperatorSub, 20},
    {TokenType::OperatorMultiply, 40},
    {TokenType::OperatorDivide, 40},
    {TokenType::OperatorModulo, 40},
    {TokenType::OperatorExponent, 80},
};

const std::string Const::sectionEntryId = Const::sectionInternalPrefix + "entry";

Const::Const(llvm::Module *module)
{
    this->module = module;

    // Register integer kind -> integer type resolvers.
    auto map = this->integerTypeResolverMap.unwrap();

    // TODO: Fix insertion error.
    // map.insert(IntegerKind::Int1, &llvm::IntegerType::getInt1Ty);
    // map.insert(IntegerKind::Int32, &llvm::IntegerType::getInt32Ty);
    // map.insert(IntegerKind::Int64, &llvm::IntegerType::getInt64Ty);
    // map.insert(IntegerKind::Int128, &llvm::IntegerType::getInt128Ty);
}

std::optional<LlvmIntTypeResolver> Const::tryGetIntTypeResolver(IntegerKind kind)
{
    return this->integerTypeResolverMap.tryGet(kind);
}
} // namespace ionir
