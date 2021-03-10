#include "Game/src/game.h"

#include "gtest/gtest.h"

TEST(GameTest, GivenPlayerPosition_WhenPositionNotOverlappingOtherEntity_ThenNoCollisionDetected) {
    Game game;
    game.Initialize();
    game.Run();

    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}