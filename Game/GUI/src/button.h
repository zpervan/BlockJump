#ifndef BLOCKJUMP_BUTTON_H
#define BLOCKJUMP_BUTTON_H

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <string>

#include "Game/Core/src/game_window.h"

namespace GUI
{

/// @TODO: Add @c SetPosition functionality to move the text and background simultaneously
class Button : public sf::Drawable
{
  public:
    explicit Button();

    /// @brief Checks whether the button is pressed.
    /// @return @c true if pressed, @c false otherwise
    bool IsPressed();

    /// @brief Checks whether the button received a single click.
    /// @return @c true if clicked, @c false otherwise
    bool IsClicked();

    /// @brief Checks whether the button is hovered.
    /// @param mouse_coordinates Mouse coordinates in the current window
    /// @return @c true if hovered, @c false otherwise
    bool IsHovered(sf::Vector2f mouse_coordinates);

    /// @brief Contains the textual part of the button which is represented with a @c sf::Text.
    /// @return Text related functionality and data - read only
    const sf::Text& Text();

    /// @brief Contains the background part of the button which is represented with a @c sf::RectangleShape.
    /// @return Background related functionality and data - read only
    const sf::RectangleShape& Background();

    /// @brief Get the sound associated with the button.
    /// @return Sound associated with button
    const sf::Sound* Sound();

    /// @brief Associate a sound when the button is active.
    /// @param sound Sound which will be added to the button
    /// @todo Define specific sounds for specific action like click or hover
    void SetSound(const sf::SoundBuffer& sound);

    /// @brief Set the button functionality in case when it's clicked.
    /// @param function Function which will be executed
    void SetFunction(std::function<void()> function);

    /// @brief Set the button label which will be displayed in the game.
    /// @param text Label string
    void SetLabel(const std::string& text);

    /// @brief Set the size of a character in pixels.
    /// @param size Pixel size
    void SetTextSize(uint size);

    /// @brief Set the button position. The upper left corner is taken in consideration.
    /// @param position
    void SetPosition(sf::Vector2f position);

    /// @brief Execute the associated button functionality.
    void ExecuteFunction();

  private: /* Functions */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private: /* Data members */
    sf::Text text_;
    sf::RectangleShape background_;
    std::function<void()> function_;
    std::unique_ptr<sf::Sound> sound_;

    bool is_hovered_{false};
    bool is_clicked_{false};
};

}  // namespace GUI

#endif  // BLOCKJUMP_BUTTON_H
