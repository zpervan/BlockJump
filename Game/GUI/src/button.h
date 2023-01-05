#ifndef BLOCKJUMP_BUTTON_H
#define BLOCKJUMP_BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace GUI
{

class Button
{
  public:
    Button();

    /// @brief Returns the state of the button
    /// @return @c true if pressed, @c false otherwise
    bool IsPressed();

    /// @brief Contains the textual part of the button which is represented with a @c sf::Text
    /// @return Text related functionality and data
    sf::Text& Text();

    /// @brief Contains the background part of the button which is represented with a @c sf::RectangleShape
    /// @return Background related functionality and data
    sf::RectangleShape& Background();

  private:
    sf::Text text_;
    sf::RectangleShape background_;
};

}  // namespace GUI

#endif  // BLOCKJUMP_BUTTON_H
