#include "pch.h"
#include "../../src/syntax/stream.hpp"
#include "../../src/syntax/token_type.hpp"

Token createTestToken(int id) {
	Token token = Token(TokenType::Unknown, std::string("test_" + std::to_string(id)), id);
	
	return token;
}

TokenStream createTestStream() {
	Token token = createTestToken(0);
	std::vector<Token> tokenVector = { token };
	TokenStream stream = TokenStream(tokenVector);

	return stream;
}

TEST(ShouldTest, Stream) {
	TokenStream stream = createTestStream();
	Token currentToken = stream.get();

	EXPECT_EQ(currentToken.getValue(), "test_0");
	EXPECT_EQ(currentToken.getType(), TokenType::Unknown);
	EXPECT_EQ(currentToken.getStartPosition(), 0);
}
