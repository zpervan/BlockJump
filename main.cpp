#include "Game/src/game.h"
#include "spdlog/spdlog.h"

///@TODO: Add jumping
///@TODO: Create floor (simple line represent a world)
///@TODO:

int main() {
    /// Create the game (window)
    spdlog::info("Starting game");
    Game game;

    game.Initialize();

    /// Run the game (process events, update the game screen)
    game.Run();

    return 0;
}