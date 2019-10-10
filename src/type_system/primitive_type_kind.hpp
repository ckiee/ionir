#pragma once

enum class PrimitiveTypeKind
{
    Void,

    Integer32,

    String,

    Character,

	Boolean,

	LastEnumValue = PrimitiveTypeKind::Boolean
};
