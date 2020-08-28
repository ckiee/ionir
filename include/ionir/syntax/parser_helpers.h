#pragma once

#define IONIR_PARSER_ASSERT(expression, T) if (!expression) { return this->noticeSentinel->makeError<T>(IONIR_NOTICE_MISC_ASSERTION_FAILED); }
#define IONIR_PARSER_ASSERT_RESULT(result, T) IONIR_PARSER_ASSERT(util::hasValue(result), T)
#define IONIR_PARSER_ASSERT_VALUE(value, T) IONIR_PARSER_ASSERT(value.has_value(), T)
#define IONIR_PARSER_TOKEN_KIND(tokenKind, T) IONIR_PARSER_ASSERT(this->is(tokenKind), T)
