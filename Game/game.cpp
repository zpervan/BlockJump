#include "Game/game.h"

#include <spdlog/spdlog.h>

#include "Game/Core/src/game_events.h"
#include "Game/World/src/block.h"
#include "Game/World/src/utility.h"
#include "Game/constants.h"
#include "Library/src/assets_manager.h"

Game::Game()
    : window_(new GameWindow(Constants::TITLE)),
      player_entity_(std::make_unique<PlayerEntity>(sf::Vector2f(25, 50))),
      game_event_system_(std::make_unique<GameEventSystem>())
{
    AssetsManager::Initialize();
    main_menu_ = std::make_unique<GUI::MainMenu>(window_.get(), game_event_system_.get());
    online_game_screen_ = std::make_unique<GUI::OnlineGameScreen>(window_.get(), game_event_system_.get());

    background_objects_.reserve(6);

    // @TODO: Move in-memory map generation somewhere more appropriate
    // @TODO: Create a non-player entity factory or builder
    Block* rec{new Block()};
    rec->SetSize({50, 50});
    rec->SetPosition({500, 505});
    rec->SetTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec);

    Block* rec1{new Block()};
    rec1->SetSize({100, 50});
    rec1->SetPosition({500, 750});
    rec1->SetTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec1);

    Block* rec2{new Block()};
    rec2->SetSize({50, 100});
    rec2->SetPosition({100, 300});
    rec2->SetTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec2);

    Block* rec3{new Block()};
    rec3->SetSize({400, 50});
    rec3->SetPosition({700, 850});
    rec3->SetTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec3);

    Block* rec4{new Block()};
    rec4->SetSize({150, 50});
    rec4->SetPosition({850, 800});
    rec4->SetTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec4);

    Block* ground{new Block()};
    ground->SetSize({1280, 200});
    ground->SetPosition({0, 900});
    ground->SetTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(ground);

    player_entity_->SetTexture(AssetsManager::GetTexture(AssetType::Player));
    // @TODO: Set it after the menu screen is done
    // window_->SetView({player_entity_->GetPosition(), {Constants::VIEW_THRESHOLD_X, Constants::VIEW_THRESHOLD_Y}});
    game_event_system_->Set(GameEvents::Menu);
}

void Game::Run()
{
    while (!window_->IsDone())
    {
        const auto event = game_event_system_->Poll();

        if (event == GameEvents::Menu)
        {
            main_menu_->Show();
        }

        if (event == GameEvents::OnlineGame)
        {
            online_game_screen_->Show();
        }

        if (event == GameEvents::Start)
        {
            Update();
            Display();
        }

        // @TODO: Implement functionalities for events
        if ((event == GameEvents::Options) || (event == GameEvents::Quit))
        {
            window_->BeginDraw();

            sf::Text not_implemented_text{};
            not_implemented_text.setCharacterSize(32);
            not_implemented_text.setFont(*AssetsManager::GetFont(FontType::Header));
            not_implemented_text.setString("Functionality not implemented");
            not_implemented_text.setFillColor(sf::Color::Black);

            window_->Draw(not_implemented_text);

            window_->EndDraw();
        }

        window_->Update();
    }
}

void Game::Update()
{
    player_entity_->Move(background_objects_);
    player_entity_->Update();

    AddGravity();

    window_->UpdatePlayerView(player_entity_->GetPosition());
}

void Game::Display()
{
    window_->BeginDraw();
    ShowEntities();
    ShowBackground();
    window_->EndDraw();
}

void Game::ShowEntities()
{
    window_->Draw(*(player_entity_->GetEntity()));
}

void Game::ShowBackground()
{
    for (auto* background_object : background_objects_)
    {
        window_->Draw(*(background_object->Get()));
    }
}

Game::~Game()
{
    spdlog::debug("Cleaning up...");
    for (auto& background_object : background_objects_)
    {
        delete background_object;
        background_object = nullptr;
    }
}

void Game::AddGravity()
{
    const auto new_player_position_y{player_entity_->GetEntity()->getPosition().y + (Constants::GRAVITY / 250)};
    const sf::FloatRect new_player_position{{player_entity_->GetPosition().x, new_player_position_y},
                                            player_entity_->GetEntity()->getSize()};

    if ((player_entity_->GetEntityState() == EntityState::Jumping) ||
        !Utility::IsColliding(new_player_position, background_objects_))
    {
        player_entity_->GetEntity()->setPosition({player_entity_->GetPosition().x, new_player_position_y});
    }
}
