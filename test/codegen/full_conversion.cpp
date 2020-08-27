#include <vector>
#include <ionir/test/compare.h>

using namespace ionir;

TEST(FullConversionTest, VisitEmptyModule) {
    EXPECT_TRUE(test::compare::inputAndOutput("module_empty.iox", "module_empty"));
}

TEST(FullConversionTest, VisitSimpleExtern) {
    EXPECT_TRUE(test::compare::inputAndOutput("extern_simple.iox", "extern_simple"));
}
