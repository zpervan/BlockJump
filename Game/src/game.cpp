#include "Game/src/game.h"
#include <thread>

void Game::Run() {
    while (window_.isOpen()) {
        // Runs on the main thread
        std::thread rendering_thread(&Game::Update, this);

        ProcessEvents();
        player_entity_.Move();

        rendering_thread.join();
        Display();
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
    rectangle_shapes_.emplace_back(player_entity_.Update());
}

void Game::Display() {
    window_.clear(sf::Color::White);
    ShowPlayer();
    window_.display();
}

void Game::ShowPlayer() {
    if (!rectangle_shapes_.empty()) {
        window_.draw(rectangle_shapes_.at(0));
        rectangle_shapes_.pop_back();
    }
}
