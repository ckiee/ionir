#pragma once

// Misc.
#define IONIR_NOTICE_MISC_UNEXPECTED_TOKEN "Encountered an unexpected token"
#define IONIR_NOTICE_MISC_UNEXPECTED_EOF "Unexpected end of input"

// Function.
#define IONIR_NOTICE_FUNCTION_CALL_UNDEFINED "Call to undefined function '%s'"
#define IONIR_NOTICE_FUNCTION_CALL_LEADING_COMMA "Leading comma in argument list is disallowed"
#define IONIR_NOTICE_FUNCTION_REDEFINED "Cannot redefine existing function '%s'"

// Instruction.
#define IONIR_NOTICE_INST_CANNOT_ALLOCATE_VOID "Cannot allocate void type"

// Value.
#define IONIR_NOTICE_VALUE_CHARACTER_MAX_ONE "Character value length must be at most a single character"
#define IONIR_NOTICE_VALUE_CONVERT_STRING_TO_INT_FAILED "Could not convert string to value, integer may be invalid or too large"
