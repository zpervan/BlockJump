#include "main_menu.h"

#include <spdlog/spdlog.h>

#include "Game/GUI/src/gui_constans.h"
#include "Game/constants.h"
#include "Library/src/assets_manager.h"

namespace GUI
{

MainMenu::MainMenu(GameWindow* window, GameEventSystem* game_event_system)
    : window_(window), game_event_system_(game_event_system)
{
    InitializeHeader();

    const std::vector<std::string> button_labels{"Start", "Online Game", "Options", "Exit"};
    InitializeButtons(button_labels);

    menu_click_.setBuffer(*AssetsManager::GetSound(SoundType::Click));
}

void MainMenu::Show()
{
    window_->BeginDraw();

    const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
    const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

    for (auto& button : buttons_)
    {
        if (button.IsHovered(mouse_game_coordinates))
        {
            menu_click_.play();
        }

        if (button.IsPressed())
        {
            button.ExecuteFunction();
        }

        window_->GetWindow()->draw(button.Background());
        window_->GetWindow()->draw(button.Text());
    }

    window_->GetWindow()->draw(header_text_);
    window_->EndDraw();
}

void MainMenu::InitializeHeader()
{
    header_text_.setString(::Constants::TITLE);
    header_text_.setCharacterSize(50);
    header_text_.setFont(*AssetsManager::GetFont(FontType::Header));
    header_text_.setFillColor(sf::Color::Black);

    // Calculate header position
    const float window_x_center = window_->GetWindow()->getSize().x / 2.0f;
    const float start_y_position = window_->GetWindow()->getSize().y * 0.1f;
    const float half_word_width = header_text_.getGlobalBounds().width / 2.0f;
    const float header_x_position = window_x_center - half_word_width;

    header_text_.setPosition(header_x_position, start_y_position);
}

void MainMenu::InitializeButtons(const std::vector<std::string>& labels)
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

    // @TODO: Make it more flexible by checking the button type
    const auto start_function = [this]() { game_event_system_->Set(GameEvents::Start); };
    buttons_[0].SetFunction(start_function);

    const auto online_game_function = [this]() { game_event_system_->Set(GameEvents::OnlineGame); };
    buttons_[1].SetFunction(online_game_function);

    const auto options_function = [this]() { game_event_system_->Set(GameEvents::Options); };
    buttons_[2].SetFunction(options_function);

    const auto quit_function = [this]() { game_event_system_->Set(GameEvents::Quit); };
    buttons_[3].SetFunction(quit_function);
}

}  // namespace GUI
