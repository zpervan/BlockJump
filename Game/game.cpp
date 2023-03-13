#include "Game/game.h"

#include <spdlog/spdlog.h>

#include "Game/Core/src/game_events.h"
#include "Game/World/src/utility.h"
#include "Game/constants.h"
#include "Library/src/assets_manager.h"
#include "Library/src/paths.h"

Game::Game()
    : window_(new GameWindow(Constants::TITLE)),
      game_event_system_(std::make_unique<GameEventSystem>()),
      map_manager_(std::make_unique<MapManager>()),
      entity_manager_(std::make_unique<EntityManager>())
{
    AssetsManager::Initialize();
    main_menu_ = std::make_unique<GUI::MainMenu>(window_.get(), game_event_system_.get());
    online_game_screen_ = std::make_unique<GUI::OnlineGameScreen>(window_.get(), game_event_system_.get());
    not_implemented_screen_ = std::make_unique<GUI::NotImplementedScreen>(window_.get(), game_event_system_.get());
    game_event_system_->Set(GameEvents::Menu);
}

void Game::Run()
{
    while (!window_->IsDone())
    {
        switch (game_event_system_->Poll())
        {
            case GameEvents::Menu:
                main_menu_->Show();
                break;

            case GameEvents::Quit:
                window_->ExitGame();
                break;

            case GameEvents::OnlineGameMenu:
                online_game_screen_->Show();
                break;

            case GameEvents::GameLoad:
                LoadGame();
                break;

            case GameEvents::GameRun:
                Update();
                Display();
                break;

            default:
                not_implemented_screen_->Show();
                break;
        }

        window_->Update();
    }
}

void Game::LoadGame()
{
    if (!map_manager_->Load(Paths::MapsDirectoryPath()))
    {
        // Return to menu if the map is not loaded correctly
        game_event_system_->Set(GameEvents::Menu);
        return;
    }

    for (const auto& background_object : map_manager_->BackgroundObjects())
    {
        entity_manager_->CreateEntity(*background_object);
    }

    if (!player_entity_)
    {
        player_entity_ = std::make_unique<PlayerEntity>(entity_manager_.get());
    }

    const auto& player_entity = map_manager_->GetPlayerEntities()[0];

    player_entity_->Get()->setPosition(player_entity->getPosition());
    player_entity_->Get()->setTexture(AssetsManager::GetTexture(AssetType::Player));

    spdlog::info("Player data loaded");

    game_event_system_->Set(GameEvents::GameRun);
}

void Game::Update()
{
    player_entity_->Move();
    player_entity_->Update();

    AddGravity();

    window_->UpdatePlayerView(player_entity_->Get()->getPosition());
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
    window_->Draw(*player_entity_);
}

void Game::ShowBackground()
{
    for (auto background_object : entity_manager_->GetEntities())
    {
        window_->Draw(background_object.second->shape);
    }
}
void Game::AddGravity()
{
    const auto new_player_position_y{player_entity_->Get()->getPosition().y + (Constants::GRAVITY / 250)};
    const sf::FloatRect new_player_position{{player_entity_->Get()->getPosition().x, new_player_position_y},
                                            player_entity_->Get()->getSize()};

    if ((player_entity_->GetEntityState() == Component::State::Entity::Jumping) || !Utility::IsColliding(new_player_position, entity_manager_->GetEntities()))
    {
        player_entity_->Get()->setPosition({player_entity_->Get()->getPosition().x, new_player_position_y});
    }
}
