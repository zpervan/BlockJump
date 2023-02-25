#include "not_implemented_screen.h"

#include "Game/GUI/src/gui_constans.h"
#include "Game/constants.h"
#include "Library/src/assets_manager.h"

namespace GUI
{

NotImplementedScreen::NotImplementedScreen(GameWindow* game_window, GameEventSystem* game_event_system)
    : window_(game_window),
      game_event_system_(game_event_system),
      text_(std::make_unique<sf::Text>()),
      button_(std::make_unique<Button>())
{
    text_->setCharacterSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    text_->setFont(*AssetsManager::GetFont(FontType::Header));
    text_->setString("Functionality not implemented");
    text_->setFillColor(sf::Color::Black);
    text_->setPosition(::Constants::WINDOW_WIDTH / 2.0f, ::Constants::WINDOW_HEIGHT / 2.0f);

    button_->SetLabel("Back");
    button_->SetTextSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    button_->SetSound(*AssetsManager::GetSound(SoundType::Click));
    button_->SetPosition({window_->GetWindowSize().x * 0.1f, window_->GetWindowSize().y * 0.05f});
    button_->SetFunction([this]() { game_event_system_->Set(GameEvents::Menu); });
}

void NotImplementedScreen::Show()
{
    window_->BeginDraw();

    const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
    const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

    if (button_->IsHovered(mouse_game_coordinates) && button_->IsClicked())
    {
        button_->ExecuteFunction();
    }

    window_->Draw(*this);
    window_->EndDraw();
}

void NotImplementedScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*text_);
    target.draw(*button_);
}

}  // namespace GUI
