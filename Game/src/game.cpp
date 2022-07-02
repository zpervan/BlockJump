#include "Game/src/game.h"

void Game::Initialize()
{
    player_entity_.SetVelocity(0.05);
    ground_.SetGroundPosition({0.0, 980.0});
}

void Game::Run()
{
    while (window_.isOpen())
    {
        // Runs on the main thread
        Update();
        player_entity_.Move(rectangle_shapes_);

        Display();
        ProcessEvents();
    }
}

void Game::ProcessEvents()
{
    sf::Event event{};
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }
    }
}

void Game::Update()
{
    rectangle_shapes_.emplace_back(player_entity_.UpdateState());
    rectangle_shapes_.emplace_back(ground_.GenerateGround());

    // @TODO: Create a non-player entity factory or builder
    sf::RectangleShape rec;
    rec.setSize({50, 50});
    rec.setPosition({500, 505});
    rec.setFillColor(sf::Color::Black);
    rectangle_shapes_.emplace_back(rec);

    sf::RectangleShape rec1;
    rec.setSize({100, 50});
    rec.setPosition({700, 600});
    rec.setFillColor(sf::Color::Black);
    rectangle_shapes_.emplace_back(rec1);

    sf::RectangleShape rec2;
    rec.setSize({50, 100});
    rec.setPosition({100, 300});
    rec.setFillColor(sf::Color::Black);
    rectangle_shapes_.emplace_back(rec2);
}

void Game::Display()
{
    window_.clear(sf::Color::White);
    ShowEntities();
    window_.display();
}

void Game::ShowEntities()
{
    if (!rectangle_shapes_.empty())
    {
        for (const auto& entity : rectangle_shapes_)
        {
            window_.draw(entity);
        }
        rectangle_shapes_.clear();
    }
}
