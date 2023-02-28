#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/World/src/utility.h"
#include "Game/constants.h"

PlayerEntity::PlayerEntity(sf::Vector2f startingPosition)
{
    spdlog::debug("Creating player entity on starting position x={} and y={}", startingPosition.x, startingPosition.y);

    Get()->setPosition(startingPosition);
    Get()->setSize({50, 50});
}

/// @TODO: Extract entities from this function so we don't have to pass it through a function
void PlayerEntity::Move(std::vector<BackgroundObject*>& entities)
{
    position_to_move_ = Get()->getPosition();

    Jump(entities);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        const sf::Vector2f new_position{position_to_move_.x - GetVelocity(), position_to_move_.y};
        if ((entity_->getPosition().x > 0) && !Utility::IsColliding({new_position, Get()->getSize()}, entities))
        {
            position_to_move_.x = new_position.x;
        }
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        const sf::Vector2f new_position{position_to_move_.x + GetVelocity(), position_to_move_.y};
        if (((entity_->getPosition().x + Get()->getSize().x) < Constants::WINDOW_WIDTH) &&
            !Utility::IsColliding({new_position, Get()->getSize()}, entities))
        {
            position_to_move_.x = new_position.x;
        }
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        const sf::Vector2f new_position{position_to_move_.x, position_to_move_.y + GetVelocity()};
        if (((entity_->getPosition().y + Get()->getSize().y) < Constants::WINDOW_HEIGHT) &&
            !Utility::IsColliding({new_position, Get()->getSize()}, entities))
        {
            position_to_move_.y = new_position.y;
        }
        return;
    }
}

void PlayerEntity::Jump(std::vector<BackgroundObject*>& entities)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (GetEntityState() != EntityState::Jumping))
    {
        spdlog::debug("Initiating jumping");
        jumping_timer_delta_ = 0.0f;
        jumping_timer_ = jumping_clock_.getElapsedTime();
        SetEntityState(EntityState::Jumping);
    }

    const sf::Vector2f ground_position{position_to_move_.x, position_to_move_.y + GetVelocity()};
    const sf::Vector2f up_position{position_to_move_.x, position_to_move_.y - GetVelocity()};

    if ((GetEntityState() == EntityState::Jumping) &&
        !Utility::IsColliding({up_position, Get()->getSize()}, entities) && jumping_timer_delta_ <= 0.2f)
    {
        jumping_timer_delta_ = jumping_clock_.getElapsedTime().asSeconds() - jumping_timer_.asSeconds();
        position_to_move_.y -= -powf(jumping_timer_delta_ / 10.0f, 3.0f) + (jumping_timer_delta_ / 10.0f) + 0.075f;
    }
    else if ((GetEntityState() == EntityState::Jumping) &&
             Utility::IsColliding({ground_position, Get()->getSize()}, entities))
    {
        spdlog::debug("Finished jumping");
        SetEntityState(EntityState::NoAction);
    }
}

void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*entity_);
}
