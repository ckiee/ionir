#include <ionir/passes/pass_manager.h>
#include "pch.h"

using namespace ionir;

TEST(PassManagerTest, InitializeEmpty) {
    PassManager passManager = PassManager();

    EXPECT_TRUE(passManager.getPasses().empty());
}

TEST(PassManagerTest, Initialize) {
    PassManager passManager = PassManager({
        PassManagerItem{
            nullptr
        }
    });

    EXPECT_FALSE(passManager.getPasses().empty());
}

TEST(PassManagerTest, GetPasses) {
    const PassManagerItem passItem = PassManagerItem{
        nullptr
    };

    PassManager passManager = PassManager({
        passItem
    });

    std::vector<PassManagerItem> passes = passManager.getPasses();

    EXPECT_EQ(passes.size(), 1);

    PassManagerItem firstPassItem = passes[0];

    EXPECT_EQ(firstPassItem.priority, passItem.priority);
    EXPECT_EQ(firstPassItem.pass, passItem.pass);
}
