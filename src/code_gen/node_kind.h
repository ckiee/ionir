#pragma once

namespace ionir
{
enum class NodeKind
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

	/**
	 * An unsigned integer literal.
	 */
	LiteralInt
};
}
