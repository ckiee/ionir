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
        [[nodiscard]] static std::string resolveIntegerKindName(IntegerKind kind);

        [[nodiscard]] static TypeKind resolveTypeKind(const std::string &id);

        [[nodiscard]] static std::optional<std::string> getConstructId(const ionshared::Ptr<Construct> &construct);

        [[nodiscard]] static std::optional<std::string> getInstId(const ionshared::Ptr<Inst> &inst) noexcept;

        [[nodiscard]] static std::optional<IntegerKind> findIntegerKindFromBitLength(uint32_t bitLength) noexcept;

        template<typename T = Construct>
        [[nodiscard]] static bool hasValue(AstResult<T> result) {
            return std::holds_alternative<T>(result);
        }

        template<typename T>
        [[nodiscard]] static bool hasValue(AstPtrResult<T> result) {
            return std::holds_alternative<ionshared::Ptr<T>>(result)
                && std::get<ionshared::Ptr<T>>(result) != nullptr;
        }

        template<typename T = Construct>
        [[nodiscard]] static T getResultValue(AstResult<T> result) {
            if (!Util::hasValue<T>(result)) {
                throw std::runtime_error("Result has no value");
            }

            return std::get<T>(result);
        }

        template<typename T = Construct>
        [[nodiscard]] static ionshared::Ptr<T> getResultValue(AstPtrResult<T> result) {
            ionshared::Ptr<T> value = Util::getResultValue<ionshared::Ptr<T>>(result);

            if (value == nullptr) {
                throw std::runtime_error("Pointer value of result is nullptr");
            }

            return value;
        }

        template<typename TFrom, typename TTo = Construct>
        [[nodiscard]] static AstPtrResult<TTo> castAstPtrResult(AstPtrResult<TFrom> fromResult, bool useDynamicPointerCast = true) {
            if (Util::hasValue(fromResult)) {
                ionshared::Ptr<TFrom> fromValue = Util::getResultValue<TFrom>(fromResult);
                ionshared::Ptr<TTo> toValue;

                /**
                 * Certain cases require use of static pointer cast instead of dynamic,
                 * otherwise it returns nullptr. An example of this would be a downcast
                 * from 'Value<IntegerType>' to 'Value<>'. In that case, it's due to it's
                 * template argument and the compiler not knowing how to convert it's
                 * corresponding field 'type'.
                 */
                if (useDynamicPointerCast) {
                    toValue = std::dynamic_pointer_cast<TTo>(fromValue);
                }
                else {
                    toValue = std::static_pointer_cast<TTo>(fromValue);
                }

                // Conversion failed; construct is nullptr.
                if (toValue == nullptr) {
                    throw std::runtime_error("Pointer cast failed; resulting value is nullptr");
                }

                return toValue;
            }

            return std::get<ionshared::Ptr<ErrorMarker>>(fromResult);
        }
    };
}
