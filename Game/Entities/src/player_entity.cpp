#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

#include "Game/constants.h"

PlayerEntity::PlayerEntity(sf::Vector2f startingPosition)
{
    spdlog::debug("Creating player entity on starting position x={} and y={}", startingPosition.x, startingPosition.y);

    GetEntity()->setPosition(startingPosition);
    GetEntity()->setSize({50, 50});
}

void PlayerEntity::Move(std::vector<BackgroundObject*>& entities)
{
    position_to_move_ = GetEntity()->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (GetPosition().x > 0)
        {
            position_to_move_.x = GetPosition().x - GetVelocity();
            position_to_move_.y = GetPosition().y;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (GetPosition().x + GetEntity()->getSize().x < Constants::WINDOW_WIDTH)
        {
            position_to_move_.x = GetPosition().x + GetVelocity();
            position_to_move_.y = GetPosition().y;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (GetPosition().y > 0)
        {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y - GetVelocity();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (GetPosition().y + GetEntity()->getSize().y < Constants::WINDOW_HEIGHT)
        {
            position_to_move_.x = GetPosition().x;
            position_to_move_.y = GetPosition().y + GetVelocity();
        }
    }
}
