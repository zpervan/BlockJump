#include "Game/game.h"

#include <spdlog/spdlog.h>

#include "Game/Core/src/game_events.h"
#include "Game/GUI/src/gui_constans.h"
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
    not_implemented_screen_ = std::make_unique<GUI::NotImplementedScreen>(window_.get(), game_event_system_.get());

    background_objects_.reserve(6);

    // @TODO: Move in-memory map generation somewhere more appropriate
    // @TODO: Create a non-player entity factory or builder
    Block* rec{new Block()};
    rec->Get()->setSize({50, 50});
    rec->Get()->setPosition({500, 505});
    rec->Get()->setTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec);

    Block* rec1{new Block()};
    rec1->Get()->setSize({100, 50});
    rec1->Get()->setPosition({500, 750});
    rec1->Get()->setTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(rec1);

    Block* rec2{new Block()};
    rec2->Get()->setSize({50, 100});
    rec2->Get()->setPosition({100, 300});
    rec2->Get()->setTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec2);

    Block* rec3{new Block()};
    rec3->Get()->setSize({400, 50});
    rec3->Get()->setPosition({700, 850});
    rec3->Get()->setTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec3);

    Block* rec4{new Block()};
    rec4->Get()->setSize({150, 50});
    rec4->Get()->setPosition({850, 800});
    rec4->Get()->setTexture(AssetsManager::GetTexture(AssetType::Brick));
    background_objects_.emplace_back(rec4);

    Block* ground{new Block()};
    ground->Get()->setSize({1280, 200});
    ground->Get()->setPosition({0, 900});
    ground->Get()->setTexture(AssetsManager::GetTexture(AssetType::DirtWithGrass));
    background_objects_.emplace_back(ground);

    player_entity_->Get()->setTexture(AssetsManager::GetTexture(AssetType::Player));
    // @TODO: Set it after the menu screen is done
    // window_->SetView({player_entity_->GetPosition(), {Constants::VIEW_THRESHOLD_X, Constants::VIEW_THRESHOLD_Y}});
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

            case GameEvents::OnlineGame:
                online_game_screen_->Show();
                break;

            case GameEvents::Start:
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

void Game::Update()
{
    player_entity_->Move(background_objects_);
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
    for (auto* background_object : background_objects_)
    {
        window_->Draw(*background_object);
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
    const auto new_player_position_y{player_entity_->Get()->getPosition().y + (Constants::GRAVITY / 250)};
    const sf::FloatRect new_player_position{{player_entity_->Get()->getPosition().x, new_player_position_y},
                                            player_entity_->Get()->getSize()};

    if ((player_entity_->GetEntityState() == EntityState::Jumping) ||
        !Utility::IsColliding(new_player_position, background_objects_))
    {
        player_entity_->Get()->setPosition({player_entity_->Get()->getPosition().x, new_player_position_y});
    }
}
