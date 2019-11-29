#include "constants.h"

namespace ionir
{
const std::string Constants::sectionInternalPrefix = ".";

const std::string Constants::sectionEntryIdentifier = Constants::sectionInternalPrefix + "entry";

Constants::Constants(llvm::Module *module)
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

std::optional<LlvmIntTypeResolver> Constants::tryGetIntTypeResolver(IntegerKind kind)
{
    return this->integerTypeResolverMap.tryGet(kind);
}
} // namespace ionir
