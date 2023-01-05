#include "button.h"

#include <SFML/Window/Mouse.hpp>

#include "Library/src/assets_manager.h"

namespace GUI
{

Button::Button()
{
    text_.setFont(*AssetsManager::GetFont());
    text_.setFillColor(sf::Color::Black);
    text_.setCharacterSize(32);
}

bool Button::IsPressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

sf::RectangleShape& Button::Background()
{
    return background_;
}

sf::Text& Button::Text()
{
    return text_;
}

}  // namespace GUI
