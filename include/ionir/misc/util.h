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

namespace ionir {
    class Inst;

    class IntegerType;

    class Util {
    public:
        static std::string resolveIntegerKindName(IntegerKind kind);

        static TypeKind resolveTypeKind(const std::string &id);

        static std::optional<std::string> getConstructId(const ionshared::Ptr<Construct> &construct);

        static std::optional<std::string> getInstId(const ionshared::Ptr<Inst> &inst) noexcept;


        static std::optional<IntegerKind> calculateIntegerKindFromBitLength(uint32_t bitLength) noexcept;

        template<typename T = Construct>
        static bool hasValue(AstResult<T> result) {
            return std::holds_alternative<T>(result);
        }

        template<typename T = Construct>
        static T getResultValue(AstResult<T> result) {
            if (!Util::hasValue(result)) {
                throw std::runtime_error("Result has no value");
            }

            return std::get<T>(result);
        }

        template<typename T = Construct>
        static ionshared::Ptr<T> getResultValue(AstPtrResult<T> result) {
            return Util::getResultValue<ionshared::Ptr<T>>(result);
        }

        template<typename TFrom, typename TTo = Construct>
        static AstPtrResult<TTo> convertAstPtrResult(AstPtrResult<TFrom> from) {
            if (Util::hasValue(from)) {
                ionshared::Ptr<TFrom> fromT = std::get<ionshared::Ptr<TFrom>>(from);
                ionshared::Ptr<Construct> construct = std::static_pointer_cast<Construct>(fromT);

                return construct->dynamicCast<TTo>();
            }

            return std::get<ionshared::Ptr<ErrorMarker>>(from);
        }
    };
}
