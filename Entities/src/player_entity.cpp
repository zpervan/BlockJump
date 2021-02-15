#include "Entities/src/player_entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RectangleShape PlayerEntity::Update() {
    sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setPosition(GetPosition().x, GetPosition().y);
    shape.setFillColor(sf::Color::Green);

    return shape;
}

void PlayerEntity::Move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        GetPosition().x > 0 ? SetPosition({GetPosition().x - GetVelocity(), GetPosition().y}) :
        SetPosition({GetPosition().x, GetPosition().y});
//        std::cout << "[LEFT]Player X position: " << GetPosition().x << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        GetPosition().x < max_width_ ? SetPosition({GetPosition().x + GetVelocity(), GetPosition().y}) :
        SetPosition({GetPosition().x, GetPosition().y});
//        std::cout << "[RIGHT]Player X position: " << GetPosition().x << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        GetPosition().y > 0 ? SetPosition({GetPosition().x, GetPosition().y - GetVelocity()}) :
        SetPosition({GetPosition().x, GetPosition().y});
//        std::cout << "[UP]Player Y position: " << GetPosition().y << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        GetPosition().y < max_height_ ? SetPosition({GetPosition().x, GetPosition().y + GetVelocity()}) :
        SetPosition({GetPosition().x, GetPosition().y});
//        std::cout << "[DOWN]Player Y position: " << GetPosition().y << std::endl;
    }
}
