#include <string>
#include <vector>
#include "pch.h"
#include "test_api/bootstrap.h"

using namespace ionir;

TEST(StreamTest, HandleGet)
{
	TokenStream stream = test::bootstrap::tokenStream();
	Token currentToken = stream.get();

	EXPECT_EQ(currentToken.getValue(), "test_0");
	EXPECT_EQ(currentToken.getType(), ionir::TokenType::Unknown);
	EXPECT_EQ(currentToken.getStartPosition(), 0);
	EXPECT_EQ(currentToken.getEndPosition(), 6);
}

TEST(StreamTest, HandleSize)
{
	// Create the initial Stream instance.
	TokenStream stream = test::bootstrap::tokenStream();

	// Should contain one item.
	EXPECT_EQ(stream.getSize(), 1);

	// Create a new Stream with more than one item.
	stream = test::bootstrap::tokenStream(2);

	// New stream instance should contain two items.
	EXPECT_EQ(stream.getSize(), 2);
}

TEST(StreamTest, HandleHasNext)
{
	// Create the initial Stream instance.
	TokenStream stream = test::bootstrap::tokenStream();

	// Stream with one item should not indicate next.
	EXPECT_FALSE(stream.hasNext());
}

TEST(StreamTest, HandleNext)
{
	// Create the initial Stream instance.
	TokenStream stream = test::bootstrap::tokenStream();

	// Extract the current item & index for comparison.
	Token token = stream.get();
	size_t index = stream.getIndex();

	// Compare tokens. They should be the same since it is the only item on the Stream.
	EXPECT_EQ(stream.next(), token);

	// Index should also be the same.
	EXPECT_EQ(stream.getIndex(), index);
}
