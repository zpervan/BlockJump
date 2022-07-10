#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include "Game/Entities/src/player_entity.h"
#include "Game/Core/src/window.h"
#include "Game/World/src/background_object.h"

#include <memory>
#include <vector>

/// @brief Manages the lifetime and screen content of the game window.
class Game
{
  public:
    Game();
    ~Game();

    /// @brief Updates the content of the game screen space.
    void Run();

    /// @TODO: Move private functions to anonymous namespaces.
  private:

    void Update();

    void Display();

    void ShowEntities();

    void ShowBackground();

  private:
    std::unique_ptr<Window> window_;
    /// @TODO: Move to a texture manager/handler class.
    std::unique_ptr<sf::Texture> texture_;
    std::unique_ptr<sf::Texture> player_texture_;

    std::unique_ptr<PlayerEntity> player_entity_;
    std::vector<BackgroundObject *> background_objects_;
};

#endif  // BLOCKJUMP_GAME_H