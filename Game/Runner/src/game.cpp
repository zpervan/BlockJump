#include "Game/Runner/src/game.h"

#include "Game/constants.h"

#include <spdlog/spdlog.h>

Game::Game() : window_(new Window(Constants::TITLE, {Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT})), texture_(new sf::Texture())
{
    entities_.reserve(5);

    texture_->loadFromFile("Game/Assets/block.png");

    // @TODO: Create a non-player entity factory or builder
    sf::RectangleShape rec;
    rec.setSize({50, 50});
    rec.setPosition({500, 505});
    rec.setFillColor(sf::Color::Yellow);
    rec.setTexture(texture_.get());
    entities_.emplace_back(rec);

    sf::RectangleShape rec1;
    rec1.setSize({100, 50});
    rec1.setPosition({700, 600});
    rec1.setFillColor(sf::Color::Cyan);
    rec1.setTexture(texture_.get());
    entities_.emplace_back(rec1);

    sf::RectangleShape rec2;
    rec2.setSize({50, 100});
    rec2.setPosition({100, 300});
    rec2.setFillColor(sf::Color::Magenta);
    rec2.setTexture(texture_.get());
    entities_.emplace_back(rec2);

    sf::RectangleShape ground;
    ground.setSize({1280, 100});
    ground.setPosition({0, 900});
    // @TODO: Brown color. Move to a top-level config file.
    ground.setFillColor({102, 70, 67});
    ground.setTexture(texture_.get());
    entities_.emplace_back(ground);

    sf::Texture * player_texture{new sf::Texture()};
    player_texture->loadFromFile("Game/Assets/player.png");

    player_entity_.SetVelocity(0.05);
    player_entity_.SetTexture(player_texture);
    entities_.emplace_back(player_entity_.UpdateState());
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
    player_entity_.Move(entities_);
    /// @TODO: Avoid creating new objects - just set the positions.
    entities_.back() = player_entity_.UpdateState();
}

void Game::Display()
{
    window_->BeginDraw();
    ShowEntities();
    window_->EndDraw();
}

void Game::ShowEntities()
{
    for (auto& entity : entities_)
    {
        window_->Draw(entity);
    }
}
