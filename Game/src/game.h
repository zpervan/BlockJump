#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include <SFML/Graphics.hpp>

/// @brief Manages the lifetime and screen content of the game window.
class Game {
public:
    /// @brief Updates the content of the game screen space.
    void Run();

    Game();

    ~Game() = default;

private:
    void ProcessEvents();

    sf::RenderWindow window_;
    sf::Event event_;
};


#endif //BLOCKJUMP_GAME_H
