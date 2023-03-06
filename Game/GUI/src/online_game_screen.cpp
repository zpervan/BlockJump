#include "online_game_screen.h"

#include <spdlog/spdlog.h>

#include <future>
#include <memory>

#include "Game/GUI/src/gui_constans.h"
#include "Library/src/assets_manager.h"

namespace GUI
{

constexpr auto server_status_text{"Server status: "};
constexpr auto alive_text{"Alive"};
constexpr auto na_text{"N/A"};
constexpr auto online_game_element_label{"Name: {} | Map: {} | Players: {} | Ping: {}"};

OnlineGameScreen::OnlineGameScreen(GameWindow* game_window, GameEventSystem* game_event_system)
    : window_(game_window),
      game_event_system_(game_event_system),
      client_(new Network::Client(grpc::CreateChannel("localhost:3500", grpc::InsecureChannelCredentials())))
{
    InitializeDrawables();
}

void OnlineGameScreen::Show()
{
    window_->BeginDraw();

    is_server_alive_ ? server_status_text_->setString(std::string(server_status_text).append(alive_text))
                     : server_status_text_->setString(std::string(server_status_text).append(na_text));

    for (std::size_t i{0}; i < drawables_.size(); i++)
    {
        if (const auto button = dynamic_cast<Button*>(drawables_[i]); button != nullptr)
        {
            const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
            const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

            if (button->IsHovered(mouse_game_coordinates) && button->IsClicked())
            {
                button->ExecuteFunction();
            }
        }

        window_->Draw(*drawables_[i]);
    }

    window_->EndDraw();
}

void OnlineGameScreen::InitializeDrawables()
{
    header_text_ = std::make_unique<sf::Text>();
    header_text_->setFont(*AssetsManager::GetFont(FontType::Header));
    header_text_->setString("Available games");
    header_text_->setFillColor(sf::Color::Black);

    const auto word_half_width = header_text_->getGlobalBounds().width / 2.0f;
    const auto window_size = window_->GetWindow()->getSize();
    header_text_->setPosition((window_size.x / 2.0f) - word_half_width, window_size.y * 0.05);

    games_list_background_ = std::make_unique<sf::RectangleShape>();
    games_list_background_->setFillColor({107, 104, 104, 255});
    games_list_background_->setSize({window_size.x * 0.9f, window_size.y * 0.8f});

    const auto background_half_width = games_list_background_->getSize().x / 2.0f;
    const auto header_position_bottom = header_text_->getGlobalBounds().top + header_text_->getGlobalBounds().height;
    games_list_background_->setPosition((window_size.x / 2.0f) - background_half_width, header_position_bottom + 10.0f);

    back_button_ = std::make_unique<Button>();
    back_button_->SetLabel("Back");
    back_button_->SetTextSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    back_button_->SetPosition({window_size.x * 0.1f, window_size.y * 0.05f});
    back_button_->SetSound(*AssetsManager::GetSound(SoundType::Click));
    back_button_->SetFunction([this]() { game_event_system_->Set(GameEvents::Menu); });

    is_server_alive_ = client_->TestConnection(rpc::DummyRequest()).ok();

    server_status_text_ = std::make_unique<sf::Text>();
    server_status_text_->setFont(*AssetsManager::GetFont(FontType::Button));
    server_status_text_->setFillColor(sf::Color::Black);
    server_status_text_->setPosition(window_size.x * 0.65f, window_size.y * 0.05f);
    is_server_alive_ ? server_status_text_->setString(std::string(server_status_text).append(alive_text))
                     : server_status_text_->setString(std::string(server_status_text).append(na_text));

    ping_button_ = std::make_unique<Button>();
    ping_button_->SetLabel("Refresh");
    ping_button_->SetTextSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
    ping_button_->SetPosition({window_size.x * 0.85f, window_size.y * 0.05f});
    ping_button_->SetSound(*AssetsManager::GetSound(SoundType::Click));
    ping_button_->SetFunction([this]() {
        // Check if the server has responded with "ok"
        is_server_alive_ = client_->TestConnection().ok();

        if (is_server_alive_)
        {
            spdlog::info("Server responded with \"OK\"");
        }
        else
        {
            spdlog::warn("Server is not reachable");
            return;
        }

        UpdateGamesList();
    });

    drawables_.emplace_back(server_status_text_.get());
    drawables_.emplace_back(header_text_.get());
    drawables_.emplace_back(games_list_background_.get());
    drawables_.emplace_back(ping_button_.get());
    drawables_.emplace_back(back_button_.get());

    UpdateGamesList();
}

void OnlineGameScreen::UpdateGamesList()
{
    const auto list_of_games = client_->ListAllGames();

    if (!list_of_games.has_value())
    {
        spdlog::info("No online games available");
        return;
    }

    /// @TODO: When updating the game list, filter out the existing or removed games from the list

    const auto background_start_x = games_list_background_->getPosition().x;
    const auto background_start_y = games_list_background_->getPosition().y;

    for (std::size_t i{0}; i < list_of_games.value()->available_games_size(); i++)
    {
        const auto& game = list_of_games.value()->available_games(i);
        const auto label = fmt::format(online_game_element_label, game.name(), game.map_name(), game.max_player_count(), game.ping());

        auto* element = new Button();
        element->SetLabel(label);
        element->SetTextSize(GUI::Constants::MAINMENU_BUTTON_TEXT_SIZE);
        element->SetPosition({background_start_x, background_start_y + (50.0f * i)});
        element->SetFunction([this]() {
            spdlog::info("Connecting to game...");
            std::thread([this]() { client_->Stream("TestUser"); }).detach();
        });

        drawables_.emplace_back(element);
    }
}

}  // namespace GUI
