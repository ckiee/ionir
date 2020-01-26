#include <ionir/misc/helpers.h>
#include <ionir/misc/inst_builder.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(InstBuilderTest, GetSection) {
    Ptr<Section> section = std::make_shared<Section>(SectionOpts{
        nullptr, SectionKind::Label,
        test::constant::foobar
    });

    Ptr<InstBuilder> builder = std::make_shared<InstBuilder>(section);

    EXPECT_EQ(builder->getSection(), section);
}
