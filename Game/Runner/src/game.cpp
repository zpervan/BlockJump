#include "Game/Runner/src/game.h"

void Game::Initialize()
{
    player_entity_.SetVelocity(0.05);
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

    // @TODO: Create a non-player entity factory or builder
    sf::RectangleShape rec;
    rec.setSize({50, 50});
    rec.setPosition({500, 505});
    rec.setFillColor(sf::Color::Black);
    rectangle_shapes_.emplace_back(rec);

    sf::RectangleShape rec1;
    rec1.setSize({100, 50});
    rec1.setPosition({700, 600});
    rec1.setFillColor(sf::Color::Cyan);
    rectangle_shapes_.emplace_back(rec1);

    sf::RectangleShape rec2;
    rec2.setSize({50, 100});
    rec2.setPosition({100, 300});
    rec2.setFillColor(sf::Color::Magenta);
    rectangle_shapes_.emplace_back(rec2);

    sf::RectangleShape ground;
    ground.setSize({1280, 100});
    ground.setPosition({0, 900});
    // @TODO: Brown color. Move to a top-level config file.
    ground.setFillColor({102, 70, 67});
    rectangle_shapes_.emplace_back(ground);
}

void Game::Display()
{
    window_.clear(sf::Color::White);
    ShowEntities();
    window_.display();
}

void Game::ShowEntities()
{
    for (const auto& entity : rectangle_shapes_)
    {
        window_.draw(entity);
    }

    rectangle_shapes_.clear();
}
