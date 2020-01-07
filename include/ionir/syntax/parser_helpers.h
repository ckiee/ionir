#pragma once

#define IONIR_PARSER_EXPECT(tokenKind) if (!this->expect(tokenKind)) { return std::nullopt; }
#define IONIR_PARSER_ASSURE(value) if (!value.has_value()) { return this->makeNotice("Unexpected parsed constructed to be null"); }
