#include "Game/Entities/src/player_entity.h"

#include "Game/Entities/src/utility.h"

#include "SFML/Graphics.hpp"
#include "spdlog/spdlog.h"

sf::RectangleShape PlayerEntity::UpdateState() {
    sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setPosition(position_);
    shape.setFillColor(sf::Color::Green);

    return shape;
}

void PlayerEntity::Move(std::vector<sf::RectangleShape>& entities)
{
    const auto & player_entity{entities.back()};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (GetPosition().x > 0 && !Utility::IsColliding(player_entity, entities, sf::Keyboard::Left)) {
            position_to_move_.x = GetPosition().x - GetVelocity();
            position_to_move_.y = GetPosition().y;
//            spdlog::debug("[LEFT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (GetPosition().x < max_width_ && !Utility::IsColliding(player_entity, entities, sf::Keyboard::Right)) {
            position_to_move_.x = GetPosition().x + GetVelocity();
            position_to_move_.y = GetPosition().y;
//            spdlog::debug("[RIGHT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (GetPosition().y > 0 && !Utility::IsColliding(player_entity, entities, sf::Keyboard::Up))  {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y - GetVelocity();
//            spdlog::debug("[UP] Player Y position: {}", GetPosition().y);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (GetPosition().y < max_height_ && !Utility::IsColliding(player_entity, entities, sf::Keyboard::Down)) {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y + GetVelocity();
//            spdlog::debug("[DOWN] Player Y position: {}", GetPosition().y);
        }
    }

    UpdatePosition();
}

sf::Vector2f PlayerEntity::GetPositionToMove() const {
    return position_to_move_;
}

void PlayerEntity::UpdatePosition() {
    position_ = position_to_move_;
}
