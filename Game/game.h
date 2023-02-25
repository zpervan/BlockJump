#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include <memory>
#include <vector>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/Entities/src/player_entity.h"
#include "Game/GUI/src/main_menu.h"
#include "Game/GUI/src/not_implemented_screen.h"
#include "Game/GUI/src/online_game_screen.h"
#include "Game/World/src/background_object.h"

/// @brief Manages the lifetime and screen content of the game window.
class Game
{
  public:
    Game();
    ~Game();

    /// @brief Updates the content of the game screen space.
    void Run();

  private: /* Functions */
    void Update();
    void Display();
    void ShowEntities();
    void ShowBackground();
    /// @TODO: Consider to move this into a Physics class functionality
    void AddGravity();

  private: /* Data members */
    std::unique_ptr<GameWindow> window_;
    std::unique_ptr<PlayerEntity> player_entity_;
    std::vector<BackgroundObject*> background_objects_;
    std::unique_ptr<GameEventSystem> game_event_system_;
    std::unique_ptr<GUI::MainMenu> main_menu_;
    std::unique_ptr<GUI::OnlineGameScreen> online_game_screen_;
    std::unique_ptr<GUI::NotImplementedScreen> not_implemented_screen_;
};

#endif  // BLOCKJUMP_GAME_H
