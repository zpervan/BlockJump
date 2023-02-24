#include "button.h"

#include <spdlog/spdlog.h>

#include <SFML/Window/Mouse.hpp>
#include <utility>

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
    sound_ = nullptr;
}

bool Button::IsPressed()
{
    const bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_pressed)
    {
        spdlog::debug("Button with label \"{}\" is pressed", text_.getString().toAnsiString());
    }

    return is_pressed;
}

bool Button::IsClicked()
{
    const bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_pressed && !is_clicked_)
    {
        spdlog::debug("Button with label \"{}\" is clicked", text_.getString().toAnsiString());
        is_clicked_ = true;
        return is_clicked_;
    }

    if (!is_pressed)
    {
        is_clicked_ = false;
        return is_clicked_;
    }

    return false;
}

bool Button::IsHovered(sf::Vector2f mouse_coordinates)
{
    const bool contains_mouse = background_.getGlobalBounds().contains(mouse_coordinates);

    // @TODO: Consider to move somewhere else as this is too much functionality for a simple checker
    if (contains_mouse)
    {
        text_.setFillColor(GUI::Constants::MAINMENU_BUTTON_HOVERED_COLOR);
        background_.setOutlineColor(GUI::Constants::MAINMENU_BUTTON_HOVERED_COLOR);
        background_.setOutlineThickness(3.0f);

        // We want to play the sound only once, therefore check if the button is already hovered
        if ((sound_ != nullptr) && !is_hovered_)
        {
            sound_->play();
        }

        is_hovered_ = true;
    }
    else
    {
        text_.setFillColor(sf::Color::Black);
        background_.setOutlineColor(sf::Color::Transparent);
        is_hovered_ = false;
    }

    return contains_mouse;
}

sf::RectangleShape& Button::Background()
{
    return background_;
}

sf::Text& Button::Text()
{
    return text_;
}

void Button::SetSound(const sf::SoundBuffer& sound)
{
    if (!sound_)
    {
        sound_ = std::make_unique<sf::Sound>();
    }

    sound_->setBuffer(sound);
}

const sf::Sound* Button::Sound()
{
    return sound_.get();
}

void Button::SetFunction(std::function<void()> function)
{
    function_ = std::move(function);
}
void Button::ExecuteFunction()
{
    function_();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text_);
    target.draw(background_);
}

}  // namespace GUI
