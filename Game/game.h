#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include <memory>
#include <vector>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/Entities/src/entity_manager.h"
#include "Game/Entities/src/player_entity.h"
#include "Game/GUI/src/main_menu.h"
#include "Game/GUI/src/not_implemented_screen.h"
#include "Game/GUI/src/online_game_screen.h"
#include "Library/src/map_manager.h"

/// @brief Manages the lifetime and screen content of the game window.
class Game
{
  public:
    Game();

    /// @brief Updates the content of the game screen space.
    void Run();

  private: /* Functions */
    void LoadGame();
    void HandleInput();
    void Update();
    void Display();
    void ShowEntities();
    void ShowBackground();
    void RestartClock();

  private: /* Data members */
    std::unique_ptr<GameWindow> window_;
    std::unique_ptr<GameEventSystem> game_event_system_;
    std::unique_ptr<PlayerEntity> player_entity_;
    std::unique_ptr<MapManager> map_manager_;
    std::unique_ptr<EntityManager> entity_manager_;
    std::unique_ptr<GUI::MainMenu> main_menu_;
    std::unique_ptr<GUI::OnlineGameScreen> online_game_screen_;
    std::unique_ptr<GUI::NotImplementedScreen> not_implemented_screen_;
    Direction direction_;
    sf::Time elapsed_time_;
    sf::Clock clock_;
};

#endif  // BLOCKJUMP_GAME_H
