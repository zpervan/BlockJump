#include "Game/src/game.h"

void Game::Run() {
    while (window_.isOpen()) {
        ProcessEvents();

        window_.clear(sf::Color::White);
        window_.display();
    }
}

void Game::ProcessEvents() {
    while (window_.pollEvent(event_)) {
        if (event_.type == sf::Event::Closed)
            window_.close();
    }
}

Game::Game() : window_{sf::VideoMode(1280, 1024), "Block game"}, event_{sf::Event()} {}
