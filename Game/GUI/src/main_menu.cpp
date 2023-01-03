#include "main_menu.h"

namespace GUI
{
MainMenu::MainMenu(GameWindow* window, GameEventSystem* game_event_system)
    : window_(window), game_event_system_(game_event_system)
{
    sf::Text start_text{};
    start_text.setFont(*AssetsManager::GetFont());
    start_text.setString("Start");
    start_text.setCharacterSize(28);
    start_text.setFillColor(sf::Color::Black);
    start_text.setPosition(window_->GetWindow()->getSize().x / 2.0f, 150.0f);

    texts_.emplace_back(start_text);

    sf::Text online_game_text{};
    online_game_text.setFont(*AssetsManager::GetFont());
    online_game_text.setString("Online game");
    online_game_text.setCharacterSize(28);
    online_game_text.setFillColor(sf::Color::Black);
    // @TODO: Implement centering menu text functionality
    online_game_text.setPosition(window_->GetWindow()->getSize().x / 2.0f, 200.0f);

    texts_.emplace_back(online_game_text);
}

void MainMenu::Show()
{
    window_->BeginDraw();

    for (const auto& text : texts_)
    {
        window_->GetWindow()->draw(text);
    }

    window_->EndDraw();
}

}  // namespace GUI
