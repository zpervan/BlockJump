#include "Entities/src/player_entity.h"

#include "SFML/Graphics.hpp"
#include "spdlog/spdlog.h"

sf::RectangleShape PlayerEntity::UpdateState() {
    sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setPosition(position_);
    shape.setFillColor(sf::Color::Green);

    return shape;
}

void PlayerEntity::Move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (GetPosition().x > 0) {
            position_to_move_.x = GetPosition().x - GetVelocity();
            position_to_move_.y = GetPosition().y;
            spdlog::debug("[LEFT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (GetPosition().x < max_width_) {
            position_to_move_.x = GetPosition().x + GetVelocity();
            position_to_move_.y = GetPosition().y;
            spdlog::debug("[RIGHT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (GetPosition().y > 0) {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y - GetVelocity();
            spdlog::debug("[UP] Player Y position: {}", GetPosition().y);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (GetPosition().y < max_height_) {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y + GetVelocity();
            spdlog::debug("[DOWN] Player Y position: {}", GetPosition().y);
        }
    }
}

sf::Vector2f PlayerEntity::GetPositionToMove() const {
    return position_to_move_;
}

void PlayerEntity::UpdatePosition() {
    position_ = position_to_move_;
}
