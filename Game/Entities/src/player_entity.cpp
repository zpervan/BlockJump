#include "Game/Entities/src/player_entity.h"

#include "Game/Entities/src/utility.h"
#include "Game/constants.h"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

PlayerEntity::PlayerEntity(sf::Vector2f startingPosition)
{
    spdlog::debug("Creating player entity on starting position x={} and y={}", startingPosition.x, startingPosition.y);

    GetEntity()->setPosition(startingPosition);
    GetEntity()->setSize({50, 50});
}

void PlayerEntity::Move(std::vector<BackgroundObject*>& entities)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (GetPosition().x > 0 && !Utility::IsColliding(*GetEntity(), entities, sf::Keyboard::Left)) {
            position_to_move_.x = GetPosition().x - GetVelocity();
            position_to_move_.y = GetPosition().y;
//            spdlog::debug("[LEFT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (GetPosition().x < Constants::WINDOW_WIDTH && !Utility::IsColliding(*GetEntity(), entities, sf::Keyboard::Right)) {
            position_to_move_.x = GetPosition().x + GetVelocity();
            position_to_move_.y = GetPosition().y;
//            spdlog::debug("[RIGHT] Player X position: {}", GetPosition().x);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (GetPosition().y > 0 && !Utility::IsColliding(*GetEntity(), entities, sf::Keyboard::Up))  {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y - GetVelocity();
//            spdlog::debug("[UP] Player Y position: {}", GetPosition().y);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (GetPosition().y < Constants::WINDOW_HEIGHT && !Utility::IsColliding(*GetEntity(), entities, sf::Keyboard::Down)) {
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
    GetEntity()->setPosition(position_to_move_);
}

void PlayerEntity::SetTexture(sf::Texture * texture)
{
    GetEntity()->setTexture(texture);
}