#include "misc/helpers.h"
#include "misc/inst_builder.h"
#include "construct/section.h"
#include "const/const.h"
#include "pch.h"

using namespace ionir;

TEST(InstBuilderTest, GetSection) {
    Ptr<Section> section = std::make_shared<Section>(SectionOpts{
            nullptr,
            SectionKind::Label,
            Const::foobar,
    });

    Ptr<InstBuilder> builder = std::make_shared<InstBuilder>(section);

    EXPECT_EQ(builder->getSection(), section);
}
