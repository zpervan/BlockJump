#include "button.h"

#include <spdlog/spdlog.h>

#include <SFML/Window/Mouse.hpp>

#include "Game/GUI/src/gui_constans.h"
#include "Library/src/assets_manager.h"

namespace GUI
{

Button::Button()
{
    /// @TODO: Make button attribute initialization more generic (remove MAINMENU constants)
    text_.setFont(*AssetsManager::GetFont(FontType::Button));
    text_.setFillColor(GUI::Constants::MAINMENU_BUTTON_TEXT_COLOR);
    text_.setCharacterSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    background_.setFillColor(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_COLOR);
    background_.setSize(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_SIZE);
}

bool Button::IsPressed()
{
    const bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_pressed)
    {
        spdlog::debug("Button with label {} is pressed", text_.getString().toAnsiString());
    }

    return is_pressed;
}

bool Button::IsHovered(sf::Vector2f mouse_coordinates)
{
    const bool is_hovered = background_.getGlobalBounds().contains(mouse_coordinates);

    if (is_hovered)
    {
        text_.setFillColor(GUI::Constants::MAINMENU_BUTTON_HOVERED_COLOR);
        background_.setOutlineColor(GUI::Constants::MAINMENU_BUTTON_HOVERED_COLOR);
        background_.setOutlineThickness(3.0f);
    }
    else
    {
        text_.setFillColor(sf::Color::Black);
        background_.setOutlineColor(sf::Color::Transparent);
    }

    return is_hovered;
}

sf::RectangleShape& Button::Background()
{
    return background_;
}

sf::Text& Button::Text()
{
    return text_;
}

void Button::SetFunction(std::function<void()> function)
{
    function_ = function;
}

void Button::ExecuteFunction()
{
    function_();
}

}  // namespace GUI
