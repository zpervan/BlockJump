#ifndef BLOCKJUMP_MAIN_MENU_H
#define BLOCKJUMP_MAIN_MENU_H

#include <SFML/Graphics/Text.hpp>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/GUI/src/button.h"
#include "Library/src/assets_manager.h"

namespace GUI
{

/// @brief Contains all functionality and rendering logic related to the main menu of the game.
class MainMenu
{
  public:
    MainMenu(GameWindow* window, GameEventSystem* game_event_system);

    /// @brief Displays the main menu on the main window screen.
    void Show();

  private:
    void PositionButtons(const std::vector<std::string>& labels);
    float CalculateButtonTextCenter(std::size_t button_index, sf::FloatRect bounds);

    GameWindow* window_;
    GameEventSystem* game_event_system_;
    std::vector<Button> buttons_;
};

}  // namespace GUI

#endif  // BLOCKJUMP_MAIN_MENU_H
