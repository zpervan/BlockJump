#include "Game/Core/src/game.h"

#include <spdlog/spdlog.h>

#include "Game/Core/src/game_events.h"
#include "Game/World/src/block.h"
#include "Game/World/src/utility.h"
#include "Game/constants.h"
#include "Library/src/assets_manager.h"

Game::Game()
    : window_(new GameWindow(Constants::TITLE)),
      player_entity_(std::make_unique<PlayerEntity>(sf::Vector2f(25, 50))),
      event_system_(std::make_unique<GameEventSystem>())
{
    AssetsManager::Initialize();

    background_objects_.reserve(6);

    // @TODO: Create a non-player entity factory or builder
    Block* rec{new Block()};
    rec->SetSize({50, 50});
    rec->SetPosition({500, 505});
    rec->SetTexture(AssetsManager::Get(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec);

    Block* rec1{new Block()};
    rec1->SetSize({100, 50});
    rec1->SetPosition({500, 750});
    rec1->SetTexture(AssetsManager::Get(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec1);

    Block* rec2{new Block()};
    rec2->SetSize({50, 100});
    rec2->SetPosition({100, 300});
    rec2->SetTexture(AssetsManager::Get(AssetType::Brick));
    background_objects_.emplace_back(rec2);

    Block* rec3{new Block()};
    rec3->SetSize({400, 50});
    rec3->SetPosition({700, 850});
    rec3->SetTexture(AssetsManager::Get(AssetType::Brick));
    background_objects_.emplace_back(rec3);

    Block* rec4{new Block()};
    rec4->SetSize({150, 50});
    rec4->SetPosition({850, 800});
    rec4->SetTexture(AssetsManager::Get(AssetType::Brick));
    background_objects_.emplace_back(rec4);

    Block* ground{new Block()};
    ground->SetSize({1280, 200});
    ground->SetPosition({0, 900});
    ground->SetTexture(AssetsManager::Get(AssetType::DirtWithGrass));
    background_objects_.emplace_back(ground);

    player_entity_->SetTexture(AssetsManager::Get(AssetType::Player));
    window_->SetView({player_entity_->GetPosition(), {Constants::VIEW_THRESHOLD_X, Constants::VIEW_THRESHOLD_Y}});
}

void Game::Run()
{
    while (!window_->IsDone())
    {
        Update();
        Display();
    }
}

void Game::Update()
{
    window_->Update();

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
