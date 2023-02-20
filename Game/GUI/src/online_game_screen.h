#ifndef BLOCKJUMP_ONLINE_GAME_SCREEN_H
#define BLOCKJUMP_ONLINE_GAME_SCREEN_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/GUI/src/button.h"
#include "Game/Network/src/client.h"

namespace GUI
{
class OnlineGameScreen
{
  public:
    OnlineGameScreen(GameWindow* game_window, GameEventSystem* game_event_system);

    /// @brief Displays the online game screen
    void Show();

  private:
    void InitializeDrawables();

    GameWindow* window_;
    GameEventSystem* game_event_system_;

    // Drawables
    std::vector<sf::Drawable*> drawables_;
    std::unique_ptr<sf::Text> header_text_;
    std::unique_ptr<sf::RectangleShape> server_list_background_;
    std::unique_ptr<Button> back_button_;
    std::unique_ptr<Button> ping_button_;
    std::unique_ptr<Network::Client> client_;
};

}  // namespace GUI

#endif  // BLOCKJUMP_ONLINE_GAME_SCREEN_H
