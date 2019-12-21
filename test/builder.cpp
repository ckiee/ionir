#include "constructs/section_kind.h"
#include "misc/inst_builder.h"
#include "pch.h"

using namespace ionir;

TEST(InstBuilderTest, GetSection)
{
    Ptr<Section> section = std::make_shared<Section>(SectionKind::Label, "foobar");
    Ptr<InstBuilder> builder = std::make_shared<InstBuilder>(section);

    EXPECT_EQ(builder->getSection(), section);
}
