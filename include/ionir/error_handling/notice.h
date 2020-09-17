#pragma once

#include <ionshared/error_handling/diagnostic_builder.h>
#include <string>

#define IONIR_NOTICE_DEFINE(name, type, message, example) \
    const static inline ionshared::Diagnostic name = ionshared::Diagnostic{ionshared::Notice(type, message), notice::errorCounter++, example}

namespace ionir::notice {
    static uint32_t errorCounter = 0;

    IONIR_NOTICE_DEFINE(
        externRedefinition,
        ionshared::NoticeType::Error,
        "Re-definition of extern not allowed",
        std::nullopt
    );
}

// Misc.
#define IONIR_NOTICE_MISC_UNEXPECTED_TOKEN "Encountered an unexpected token"
#define IONIR_NOTICE_MISC_UNEXPECTED_EOF "Unexpected end of input"
#define IONIR_NOTICE_MISC_ASSERTION_FAILED "Assertion failed"

// Function.
#define IONIR_NOTICE_FUNCTION_CALL_UNDEFINED "Call to undefined function '%s'"
#define IONIR_NOTICE_FUNCTION_CALL_LEADING_COMMA "Leading comma in argument list is disallowed"
#define IONIR_NOTICE_FUNCTION_RETURN_TYPE_MISMATCH "Function '%s' return type and return value type mismatch"
#define IONIR_NOTICE_FUNCTION_REDEFINED "Cannot redefine existing function '%s'"

// Instruction.
#define IONIR_NOTICE_INST_ALLOCA_VOID "Cannot allocate void type"
#define IONIR_NOTICE_INST_STORE_UNRESOLVED_REF "Cannot store value to an unresolved reference '%s'"
#define IONIR_NOTICE_INST_STORE_TYPE_MISMATCH "Cannot store value with different type than what was allocated to '%s'"

// Value.
#define IONIR_NOTICE_VALUE_CHARACTER_MAX_ONE "Character value length must be at most a single character"
#define IONIR_NOTICE_VALUE_CONVERT_STRING_TO_INT_FAILED "Could not convert string to value, integer may be invalid or too large"
