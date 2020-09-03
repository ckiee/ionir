#pragma once

#include <optional>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <string_view>
#include <cmath>
#include <ionir/construct/type/integer_type.h>
#include <ionir/syntax/ast_result.h>
#include <ionir/const/const_name.h>

namespace ionir::util {
    class Inst;

    class IntegerType;

    [[nodiscard]] std::string resolveIntegerKindName(IntegerKind kind);

    [[nodiscard]] TypeKind resolveTypeKind(const std::string &id);

    [[nodiscard]] std::optional<std::string> getConstructId(const ionshared::Ptr<Construct> &construct);

    [[nodiscard]] std::optional<std::string> getInstId(const ionshared::Ptr<ionir::Inst> &inst) noexcept;

    [[nodiscard]] std::optional<IntegerKind> findIntegerKindFromBitLength(uint32_t bitLength) noexcept;
}
