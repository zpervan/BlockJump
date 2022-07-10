#include "Game/Core/src/game.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game/World/src/block.h"
#include "Game/Core/src/utility.h"
#include "Game/constants.h"

Game::Game()
    : window_(new Window(Constants::TITLE, {Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT})),
      texture_(std::make_unique<sf::Texture>()),
      player_texture_(std::make_unique<sf::Texture>()),
      player_entity_(std::make_unique<PlayerEntity>(sf::Vector2f(50, 50)))
{
    texture_->loadFromFile("Game/Assets/block.png");

    background_objects_.reserve(5);

    // @TODO: Create a non-player entity factory or builder
    Block* rec{new Block()};
    rec->SetSize({50, 50});
    rec->SetPosition({500, 505});
    rec->SetFillColor(sf::Color::Yellow);
    rec->SetTexture(texture_.get());
    background_objects_.emplace_back(rec);

    Block* rec1{new Block()};
    rec1->SetSize({100, 50});
    rec1->SetPosition({700, 600});
    rec1->SetFillColor(sf::Color::Cyan);
    rec1->SetTexture(texture_.get());
    background_objects_.emplace_back(rec1);

    Block* rec2{new Block()};
    rec2->SetSize({50, 100});
    rec2->SetPosition({100, 300});
    rec2->SetFillColor(sf::Color::Magenta);
    rec2->SetTexture(texture_.get());
    background_objects_.emplace_back(rec2);

    Block* ground{new Block()};
    ground->SetSize({1280, 100});
    ground->SetPosition({0, 900});
    // @TODO: Brown color. Move to a top-level config file.
    ground->SetFillColor({102, 70, 67});
    ground->SetTexture(texture_.get());
    background_objects_.emplace_back(ground);

    player_texture_->loadFromFile("Game/Assets/player.png");
    player_entity_->SetTexture(player_texture_.get());
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

    if(!Utility::IsColliding(*player_entity_, background_objects_))
    {
        player_entity_->Update();
        AddGravity();
    }
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
    const auto & player_size_y = player_entity_->GetEntity()->getSize().y;

    if((player_entity_->GetPosition().y + player_size_y) < (Constants::WINDOW_HEIGHT - 200))
    {
        const auto new_player_position_y{player_entity_->GetEntity()->getPosition().y + (Constants::GRAVITY / 500)};
        player_entity_->GetEntity()->setPosition({player_entity_->GetPosition().x, new_player_position_y});
    }
}
