#include "Game/src/game.h"
#include "Game/src/utility.h"
#include <thread>
#include <iostream>

void Game::Initialize() {
    player_entity_.SetVelocity(0.3);
    ground_.SetGroundPosition({0.0, 980.0});
}

void Game::Run() {
    while (window_.isOpen()) {
        // Runs on the main thread
        std::thread rendering_thread(&Game::Update, this);
        player_entity_.Move();

        if (!rectangle_shapes_.empty()) {
            if (!Utility::AreObjectsColliding(rectangle_shapes_.at(0), rectangle_shapes_)) {
                std::cout << "Objects are not colliding" << std::endl;
                player_entity_.UpdatePosition();
            }
        }

        rendering_thread.join();
        Display();
        ProcessEvents();
    }
}

void Game::ProcessEvents() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

void Game::Update() {
    rectangle_shapes_.emplace_back(player_entity_.UpdateState());
    sf::RectangleShape rec;
    rec.setSize({50, 50});
    rec.setPosition({500, 505});
    rec.setFillColor(sf::Color::Black);
    rectangle_shapes_.emplace_back(rec);
    rectangle_shapes_.emplace_back(ground_.GenerateGround());
}

void Game::Display() {
    window_.clear(sf::Color::White);
    ShowEntities();
    window_.display();
}

void Game::ShowEntities() {
    if (!rectangle_shapes_.empty()) {
        for (const auto &entity : rectangle_shapes_) {
            window_.draw(entity);
        }
        rectangle_shapes_.clear();
    }
}
