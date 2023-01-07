#ifndef BLOCKJUMP_BUTTON_H
#define BLOCKJUMP_BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace GUI
{

/// @TODO: Add @c SetPosition functionality to move the text and background simultaneously
class Button
{
  public:
    Button();

    /// @brief Checks whether the button is pressed.
    /// @return @c true if pressed, @c false otherwise
    bool IsPressed();

    /// @brief Checks whether the button is hovered.
    /// @param mouse_coordinates Mouse coordinates in the current window
    /// @return @c true if hovered, @c false otherwise
    bool IsHovered(sf::Vector2f mouse_coordinates);

    /// @brief Contains the textual part of the button which is represented with a @c sf::Text.
    /// @return Text related functionality and data
    sf::Text& Text();

    /// @brief Contains the background part of the button which is represented with a @c sf::RectangleShape.
    /// @return Background related functionality and data
    sf::RectangleShape& Background();

    /// @brief Set the button functionality in case when it's clicked.
    /// @param function Function which will be executed
    void SetFunction(std::function<void()> function);

    /// @brief Execute the associated button functionality.
    void ExecuteFunction();

  private:
    sf::Text text_;
    sf::RectangleShape background_;
    std::function<void()> function_;
};

}  // namespace GUI

#endif  // BLOCKJUMP_BUTTON_H
