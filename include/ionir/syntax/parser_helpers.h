#pragma once

#define IONIR_PARSER_ASSERT(expression) if (!expression) { return std::nullopt; }
#define IONIR_PARSER_EXPECT(tokenKind) IONIR_PARSER_ASSERT(this->expect(tokenKind))

// TODO: Also compare vs nullptr. Currently error-ing build.
#define IONIR_PARSER_ASSURE(value) if (!value.has_value() /*|| (value == nullptr)*/) { return this->makeNotice("Unexpected parsed constructed to be null"); }
