#include "pch.h"
#include "syntax/stream.hpp"
#include <string>
#include <vector>

using namespace ::testing;

ionir::Token createTestToken(int id)
{
	ionir::Token token = ionir::Token(ionir::TokenType::Unknown, std::string("test_" + std::to_string(id)), id);

	return token;
}

ionir::TokenStream createTestStream()
{
	ionir::Token token = createTestToken(0);
	std::vector<ionir::Token> tokenVector = {token};
	ionir::TokenStream stream = ionir::TokenStream(tokenVector);

	return stream;
}

TEST(StreamTest, GetCurrent)
{
	ionir::TokenStream stream = createTestStream();
	ionir::Token currentToken = stream.get();

	EXPECT_EQ(currentToken.getValue(), "test_0");
	EXPECT_EQ(currentToken.getType(), ionir::TokenType::Unknown);
	EXPECT_EQ(currentToken.getStartPosition(), 0);
}
