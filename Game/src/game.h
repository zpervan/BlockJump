#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Entities/src/player_entity.h"

/// @brief Manages the lifetime and screen content of the game window.
class Game
{
  public:
    /// @brief Updates the content of the game screen space.
    void Run();

  private:
    void ProcessEvents();

    void Update();

    void Display();

    void ShowPlayer();

    sf::RenderWindow window_{sf::VideoMode(1280, 1024), "Block game"};
    PlayerEntity player_entity_;
    std::vector<sf::RectangleShape> rectangle_shapes_;
};

#endif  // BLOCKJUMP_GAME_H
