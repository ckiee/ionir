#pragma once

#include <ionshared/diagnostics/diagnostic_builder.h>

#define IONIR_NOTICE_DEFINE(name, type, message, example) \
    const static inline ionshared::Diagnostic name =\
        ionshared::Diagnostic{\
            type,\
            message,\
            std::nullopt,\
            diagnostic::errorCounter++,\
            example\
        }

namespace ionir::diagnostic {
    static uint32_t errorCounter = 0;

    IONIR_NOTICE_DEFINE(
        externRedefinition,
        ionshared::DiagnosticType::Error,
        "Re-definition of extern not allowed",
        std::nullopt
    );

    IONIR_NOTICE_DEFINE(
        entryPointRedefinition,
        ionshared::DiagnosticType::Error,
        "Entry point function had already previously been declared",
        std::nullopt
    );

    IONIR_NOTICE_DEFINE(
        functionMissingEntryBasicBlock,
        ionshared::DiagnosticType::Error,
        "Function is missing an entry basic block",
        std::nullopt
    );

    IONIR_NOTICE_DEFINE(
        functionMissingReturnValue,
        ionshared::DiagnosticType::Error,
        "Function whose prototype's return type is not void must return a value",
        std::nullopt
    );

    IONIR_NOTICE_DEFINE(
        functionRedefinitionDiffArgs,
        ionshared::DiagnosticType::Error,
        "Re-definition of function with a different amount arguments",
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
