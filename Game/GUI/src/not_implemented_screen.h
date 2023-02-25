#ifndef BLOCKJUMP_NOT_IMPLEMENTED_SCREEN_H
#define BLOCKJUMP_NOT_IMPLEMENTED_SCREEN_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>

#include "Game/Core/src/game_events.h"
#include "Game/Core/src/game_window.h"
#include "Game/GUI/src/button.h"

namespace GUI
{

/// @brief Dummy screen for non implemented functionalities.
class NotImplementedScreen : public sf::Drawable
{
  public:
    NotImplementedScreen(GameWindow* game_window, GameEventSystem* game_event_system);

    /// @brief Shows the not implemented screen containing an info text and a button.
    void Show();

  private: /* Functions */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private: /* Data members */
    GameWindow* window_;
    GameEventSystem* game_event_system_;
    std::unique_ptr<sf::Text> text_;
    std::unique_ptr<GUI::Button> button_;
};

}  // namespace GUI

#endif  // BLOCKJUMP_NOT_IMPLEMENTED_SCREEN_H
