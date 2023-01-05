#include "main_menu.h"

#include <spdlog/spdlog.h>

#include "Game/GUI/src/gui_constans.h"

namespace GUI
{

MainMenu::MainMenu(GameWindow* window, GameEventSystem* game_event_system)
    : window_(window), game_event_system_(game_event_system)
{
    Button start_button;
    start_button.Text().setFont(*AssetsManager::GetFont());
    start_button.Text().setString("Start");
    start_button.Text().setCharacterSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    start_button.Text().setFillColor(GUI::Constants::MAINMENU_BUTTON_TEXT_COLOR);
    start_button.Text().setPosition(window_->GetWindow()->getSize().x / 2.0f, 150.0f);
    start_button.Background().setPosition(window_->GetWindow()->getSize().x / 2.0f, 150.0f);
    start_button.Background().setSize(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_SIZE);
    start_button.Background().setFillColor(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_COLOR);

    buttons_.emplace_back(start_button);

    Button online_game_button{};
    online_game_button.Text().setFont(*AssetsManager::GetFont());
    online_game_button.Text().setString("Online game");
    online_game_button.Text().setCharacterSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    online_game_button.Text().setFillColor(GUI::Constants::MAINMENU_BUTTON_TEXT_COLOR);
    // @TODO: Implement centering menu text functionality
    online_game_button.Text().setPosition(window_->GetWindow()->getSize().x / 2.0f, 200.0f);
    online_game_button.Background().setPosition(window_->GetWindow()->getSize().x / 2.0f, 200.0f);
    online_game_button.Background().setSize(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_SIZE);
    online_game_button.Background().setFillColor(GUI::Constants::MAINMENU_BUTTON_BACKGROUND_COLOR);

    buttons_.emplace_back(online_game_button);
}

void MainMenu::Show()
{
    window_->BeginDraw();

    const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
    const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

    for (auto& button : buttons_)
    {
        if (button.Text().getGlobalBounds().contains(mouse_game_coordinates))
        {
            button.Text().setFillColor(sf::Color::Red);
            if (button.IsPressed())
            {
                game_event_system_->Set(GameEvents::Start);
            }
        }
        else
        {
            button.Text().setFillColor(sf::Color::Black);
        }

        window_->GetWindow()->draw(button.Background());
        window_->GetWindow()->draw(button.Text());
    }

    window_->EndDraw();
}

}  // namespace GUI
