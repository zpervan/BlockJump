#include "Game/Core/src/game.h"

#include "spdlog/spdlog.h"

/// @TODO: Create texture manager/handler class

int main() {
// Use debug messages in non-optimizes (debug) mode
#ifndef __OPTIMIZE__
    spdlog::set_level(spdlog::level::debug);
#endif

    /// Create the game (window)
    spdlog::info("Starting game");
    Game game;

    /// Run the game (process events, update the game screen)
    game.Run();

    return 0;
}