#pragma once

namespace ionir
{
enum class ConstructKind
{
	Type,

	/**
	 * A block, possibly containing statements.
	 */
	Block,

	/**
	 * Function prototype used to declare externs
	 * or actual functions.
	 */
	Prototype,

	Function,

	/**
	 * An external function definition.
	 */
	Extern,

	Instruction,

	Value,

	GlobalVariable,

	Section
};
}
