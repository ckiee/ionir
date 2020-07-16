#include <optional>
#include <ionir/construct/pseudo/ref.h>
#include <ionir/construct/inst/return.h>
#include <ionir/misc/helpers.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(RefTest, Initialize) {
    Ref<> ref = Ref<>(test::constant::foobar, nullptr);

    EXPECT_EQ(ref.getId(), test::constant::foobar);
    EXPECT_EQ(ref.getOwner(), nullptr);
    EXPECT_FALSE(ref.getValue().has_value());
}

TEST(RefTest, SetId) {
    Ref<> ref = Ref<>(test::constant::foo, nullptr);

    ref.setId(test::constant::bar);

    EXPECT_EQ(ref.getId(), test::constant::bar);
}

TEST(RefTest, SetOwner) {
    Ref<> ref = Ref<>(test::constant::foobar, nullptr);
    ionshared::Ptr<ReturnInst> returnInst = std::make_shared<ReturnInst>(ReturnInstOpts{});

    ref.setOwner(returnInst);

    EXPECT_EQ(ref.getOwner(), returnInst);
}

TEST(RefTest, SetValue) {
    Ref<> ref = Ref<>(test::constant::foobar, nullptr);
    ionshared::Ptr<ReturnInst> returnInst = std::make_shared<ReturnInst>(ReturnInstOpts{});

    ref.setOwner(returnInst);

    EXPECT_EQ(ref.getOwner(), returnInst);
}
