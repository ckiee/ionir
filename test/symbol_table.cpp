using namespace ionir;

TEST(SymbolTableTest, T

) {
Lexer lexer = Lexer("test input");

EXPECT_EQ(lexer

.

getInput(),

"test input");
}
