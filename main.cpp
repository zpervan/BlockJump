#include "Game/src/game.h"

///@TODO: Add jumping
///@TODO: Create floor (simple line represent a world)

int main() {
    /// Create the game (window)
    Game game;

    /// Run the game (process events, update the game screen)
    game.Run();

    return 0;
}