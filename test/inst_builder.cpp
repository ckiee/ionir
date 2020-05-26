#include <ionir/misc/helpers.h>
#include <ionir/misc/inst_builder.h>
#include <ionir/misc/bootstrap.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(InstBuilderTest, GetSection) {
    Ptr<BasicBlock> section = Bootstrap::basicBlock();
    Ptr<InstBuilder> builder = section->createBuilder();

    EXPECT_EQ(builder->getSection(), section);
}

TEST(InstBuilderTest, CreateReturn) {
    // TODO
}
