#pragma once

#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionir::diagnostics {
    const ionshared::Diagnostic internalAssertionFailed {
        ionshared::Notice(
            ionshared::NoticeType::InternalError,
            "Assertion failed"
        )
    };

    const ionshared::Diagnostic syntaxUnexpectedToken {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Unexpected token"
        )
    };

    const ionshared::Diagnostic syntaxCharacterMax {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Maximum length of a character must be one"
        )
    };

    const ionshared::Diagnostic functionMissingEntry {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Function '%s' is missing an entry basic block"
        )
    };

    const ionshared::Diagnostic functionCallToUndefined {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Call to an undefined function '%s'"
        )
    };

    const ionshared::Diagnostic functionAlreadyDefined {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Function '%s' was already previously defined"
        )
    };

    const ionshared::Diagnostic functionCallLeadingComma {
        ionshared::Notice(
            ionshared::NoticeType::Warning,
            "Leading comma in argument list"
        ),

        std::nullopt,

        "There's an extra leading comma in the argument list: 'foo(arg1, arg2,)'\nWhen it should be: 'foo(arg1, arg2)'"
    };

    const ionshared::Diagnostic instAllocaVoid {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Cannot allocate void type"
        )
    };

    const ionshared::Diagnostic instStoreTypeMismatch {
        ionshared::Notice(
            ionshared::NoticeType::Error,
            "Trying to store a value with type '%s' but expecting '%s'"
        )
    };
}
