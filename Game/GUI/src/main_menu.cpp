#include "main_menu.h"

#include <spdlog/spdlog.h>

#include "Game/GUI/src/gui_constans.h"

namespace GUI
{

MainMenu::MainMenu(GameWindow* window, GameEventSystem* game_event_system)
    : window_(window), game_event_system_(game_event_system)
{
    const std::vector<std::string> button_labels{"Start", "Online Game", "Options", "Exit"};
    PositionButtons(button_labels);
}

void MainMenu::Show()
{
    window_->BeginDraw();

    const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
    const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

    for (auto& button : buttons_)
    {
        if (button.IsHovered(mouse_game_coordinates) && button.IsPressed())
        {
            // @TODO: Implement function execution when specific button is pressed
            game_event_system_->Set(GameEvents::Start);
        }

        window_->GetWindow()->draw(button.Background());
        window_->GetWindow()->draw(button.Text());
    }

    window_->EndDraw();
}

void MainMenu::PositionButtons(const std::vector<std::string>& labels)
{
    const float window_x_center = window_->GetWindow()->getSize().x / 2.0f;
    const float start_y_position = window_->GetWindow()->getSize().y * 0.3f;
    const float y_step = window_->GetWindow()->getSize().y * 0.05f;
    const float background_half_width = GUI::Constants::MAINMENU_BUTTON_BACKGROUND_SIZE.x / 2.0f;

    for (std::size_t i{0}; i < labels.size(); i++)
    {
        Button button{};
        button.Text().setString(labels[i]);

        // Calculate button text position
        const float half_word_width = button.Text().getGlobalBounds().width / 2.0f;
        const float label_x_position = window_x_center - half_word_width;
        button.Text().setPosition(label_x_position, start_y_position + (y_step * i));

        // Calculate button background position
        button.Background().setPosition(window_x_center - background_half_width, start_y_position + (y_step * i));

        buttons_.emplace_back(std::move(button));
    }
}

}  // namespace GUI
