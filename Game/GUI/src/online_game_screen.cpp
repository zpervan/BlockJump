#include "online_game_screen.h"

#include <spdlog/spdlog.h>

#include "Library/src/assets_manager.h"

namespace GUI
{

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

    drawables_.emplace_back(header_text_.get());
    drawables_.emplace_back(server_list_background_.get());

    /// @TODO: Add hoverable list elements (make new component)

    for (auto drawable : drawables_)
    {
        window_->Draw(*drawable);
    }

    const auto mouse_position = sf::Mouse::getPosition(*window_->GetWindow());
    const auto mouse_game_coordinates = window_->GetWindow()->mapPixelToCoords(mouse_position);

    if (back_button_->IsHovered(mouse_game_coordinates) && back_button_->IsClicked())
    {
        back_button_->ExecuteFunction();
    }

    if (ping_button_->IsHovered(mouse_game_coordinates) && ping_button_->IsClicked())
    {
        ping_button_->ExecuteFunction();
    }

    /// @TODO: Refactor so it can be added to the drawable list, ideally as a single Button object
    window_->Draw(back_button_->Text());
    window_->Draw(back_button_->Background());

    window_->Draw(ping_button_->Text());
    window_->Draw(ping_button_->Background());

    drawables_.clear();

    window_->EndDraw();
}

void OnlineGameScreen::InitializeDrawables()
{
    auto* header_text = new sf::Text;
    header_text->setFont(*AssetsManager::GetFont(FontType::Header));
    header_text->setString("Available games");
    header_text->setFillColor(sf::Color::Black);

    const auto word_half_width = header_text->getGlobalBounds().width / 2.0f;
    const auto window_size = window_->GetWindow()->getSize();
    header_text->setPosition((window_size.x / 2.0f) - word_half_width, window_size.y * 0.05);

    header_text_.reset(header_text);

    auto* server_list_background = new sf::RectangleShape;
    server_list_background->setFillColor({107, 104, 104, 255});
    server_list_background->setSize({window_size.x * 0.9f, window_size.y * 0.8f});

    const auto background_half_width = server_list_background->getSize().x / 2.0f;
    const auto header_position_bottom = header_text_->getGlobalBounds().top + header_text_->getGlobalBounds().height;
    server_list_background->setPosition((window_size.x / 2.0f) - background_half_width, header_position_bottom + 10.0f);

    server_list_background_.reset(server_list_background);

    auto* back_button = new Button();
    back_button->Text().setString("Back");
    back_button->Text().setFillColor(sf::Color::Black);
    back_button->SetFunction([this]() { game_event_system_->Set(GameEvents::Menu); });

    back_button_.reset(back_button);

    auto* ping_button = new Button();
    ping_button->Text().setString("Ping Server");
    ping_button->Text().setFillColor(sf::Color::Black);
    ping_button->Text().setPosition(window_size.x * 0.85, window_size.y * 0.05);
    ping_button->Background().setPosition(window_size.x * 0.85, window_size.y * 0.05);
    ping_button->SetFunction([this]() {
        spdlog::debug("Pinging server...");

        rpc::DummyRequest request;
        request.set_dummy_data("Test ping from game client");

        spdlog::debug(fmt::format("Response from client: {}", client_->TestConnection(request)));
    });

    ping_button_.reset(ping_button);
}

}  // namespace GUI
