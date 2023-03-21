#include "Game/game.h"

#include <spdlog/spdlog.h>

#include "Game/Core/src/game_events.h"
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
                HandleInput();
                Update();
                Display();
                RestartClock();
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
        const auto id = entity_manager_->CreateEntity(*background_object);

        auto position = new Component::Position;
        position->x = background_object->getPosition().x;
        position->y = background_object->getPosition().y;
        entity_manager_->AddComponent(id, position);

        /// @TODO: Components data should be a part of the background object
        entity_manager_->AddComponent(id, new Component::Collidable);
    }

    spdlog::info("Background tiles loaded");

    if (!player_entity_)
    {
        player_entity_ = std::make_unique<PlayerEntity>(entity_manager_.get());
    }

    const auto& player_entity = map_manager_->GetPlayerEntities()[0];

    /// @TODO: -200 is just added temporary as the player start inside the tile - create new map
    player_entity_->Get()->setPosition({player_entity->getPosition().x, player_entity->getPosition().y - 200});
    player_entity_->Get()->setTexture(AssetsManager::GetTexture(AssetType::Player));

    const auto player_entity_id = entity_manager_->CreateEntity(*player_entity_->Get());
    player_entity_->SetId(player_entity_id);

    entity_manager_->AddComponent(player_entity_id, new Component::Collidable);

    spdlog::info("Player data loaded");

    game_event_system_->Set(GameEvents::GameRun);
}

void Game::HandleInput()
{
    direction_ = Direction::None;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction_ = Direction::Up;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction_ = Direction::Down;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction_ = Direction::Left;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction_ = Direction::Right;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player_entity_->EntityState() != Component::State::Entity::Jumping)
    {
        player_entity_->SetEntityState(Component::State::Entity::JumpStart);
    }
}

void Game::Update()
{
    player_entity_->SetDirection(direction_);
    player_entity_->Update(elapsed_time_.asSeconds());

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
        if (background_object.first == player_entity_->Id())
        {
            continue;
        }

        window_->Draw(background_object.second->shape);
    }
}

void Game::RestartClock()
{
    elapsed_time_ = clock_.restart();
}
