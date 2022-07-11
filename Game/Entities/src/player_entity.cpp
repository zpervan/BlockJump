#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/constants.h"

PlayerEntity::PlayerEntity(sf::Vector2f startingPosition)
    : jumping_clock_(sf::Clock())
{
    spdlog::debug("Creating player entity on starting position x={} and y={}", startingPosition.x, startingPosition.y);

    GetEntity()->setPosition(startingPosition);
    GetEntity()->setSize({50, 50});
}

void PlayerEntity::Move(std::vector<BackgroundObject*>& entities)
{
    position_to_move_ = GetEntity()->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (GetEntityState() != EntityState::Jumping))
    {
        spdlog::debug("Initiating jumping");
        jumping_timer_delta_ = 0;
        jumping_timer_ = jumping_clock_.getElapsedTime();
        SetEntityState(EntityState::Jumping);
    }

    if ((GetEntityState() == EntityState::Jumping) && jumping_timer_delta_ <= 0.2f)
    {
        jumping_timer_delta_ = jumping_clock_.getElapsedTime().asSeconds() - jumping_timer_.asSeconds();
        position_to_move_.y -= -std::pow(jumping_timer_delta_ / 10, 3) + (jumping_timer_delta_ / 10) + 0.075;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (GetPosition().x > 0)
        {
            position_to_move_.x -= GetVelocity();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if ((GetPosition().x + GetEntity()->getSize().x) < Constants::WINDOW_WIDTH)
        {
            position_to_move_.x += GetVelocity();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if ((GetPosition().y + GetEntity()->getSize().y) < Constants::WINDOW_HEIGHT)
        {
            position_to_move_.y += GetVelocity();
        }
    }
}
