#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include "Game/Entities/src/player_entity.h"
#include "window.h"

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

#include <vector>
#include <memory>

/// @brief Manages the lifetime and screen content of the game window.
class Game
{
  public:
    Game();

    /// @brief Updates the content of the game screen space.
    void Run();

  private:

    void Update();

    void Display();

    void ShowEntities();

  private:
    std::unique_ptr<Window> window_;
    PlayerEntity player_entity_;
    std::vector<sf::RectangleShape> entities_;
};

#endif  // BLOCKJUMP_GAME_H
