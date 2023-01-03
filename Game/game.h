#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include <memory>
#include <vector>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/Entities/src/player_entity.h"
#include "Game/GUI/src/main_menu.h"
#include "Game/World/src/background_object.h"

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

    void AddGravity();

  private:
    std::unique_ptr<GameWindow> window_;
    std::unique_ptr<PlayerEntity> player_entity_;
    std::vector<BackgroundObject *> background_objects_;
    std::unique_ptr<GameEventSystem> game_event_system_;
    std::unique_ptr<GUI::MainMenu> main_menu_;
};

#endif  // BLOCKJUMP_GAME_H
