#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/World/src/utility.h"
#include "Game/constants.h"

PlayerEntity::PlayerEntity(EntityManager* entity_manager) : BaseEntity(entity_manager)
{
    spdlog::debug("Creating player entity");
    entity_->setSize({50.0f, 50.0f});
}

void PlayerEntity::Move()
{
    position_to_move_ = entity_->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        const sf::Vector2f new_position{position_to_move_.x - Velocity(), position_to_move_.y};
        if ((entity_->getPosition().x > 0) &&
            !Utility::IsColliding({new_position, entity_->getSize()}, entity_manager_->GetEntities()))
        {
            position_to_move_.x = new_position.x;
        }
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        const sf::Vector2f new_position{position_to_move_.x + Velocity(), position_to_move_.y};
        if (((entity_->getPosition().x + entity_->getSize().x) < Constants::WINDOW_WIDTH) &&
            !Utility::IsColliding({new_position, entity_->getSize()}, entity_manager_->GetEntities()))
        {
            position_to_move_.x = new_position.x;
        }
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        const sf::Vector2f new_position{position_to_move_.x, position_to_move_.y + Velocity()};
        if (((entity_->getPosition().y + entity_->getSize().y) < Constants::WINDOW_HEIGHT) &&
            !Utility::IsColliding({new_position, entity_->getSize()}, entity_manager_->GetEntities()))
        {
            position_to_move_.y = new_position.y;
        }
        return;
    }
}

void PlayerEntity::Jump()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (EntityState() != Component::State::Entity::Jumping))
    {
        spdlog::debug("Initiating jumping");
        jumping_timer_delta_ = 0.0f;
        jumping_timer_ = jumping_clock_.getElapsedTime();
        SetEntityState(Component::State::Entity::Jumping);
    }

    const sf::Vector2f ground_position{position_to_move_.x, position_to_move_.y + Velocity()};
    const sf::Vector2f up_position{position_to_move_.x, position_to_move_.y - Velocity()};

    if ((EntityState() == Component::State::Entity::Jumping) &&
        !Utility::IsColliding({up_position, entity_->getSize()}, entity_manager_->GetEntities()) &&
        jumping_timer_delta_ <= 0.2f)
    {
        jumping_timer_delta_ = jumping_clock_.getElapsedTime().asSeconds() - jumping_timer_.asSeconds();
        position_to_move_.y -= -powf(jumping_timer_delta_ / 10.0f, 3.0f) + (jumping_timer_delta_ / 10.0f) + 0.075f;
    }
    else if ((EntityState() == Component::State::Entity::Jumping) &&
             Utility::IsColliding({ground_position, entity_->getSize()}, entity_manager_->GetEntities()))
    {
        spdlog::debug("Finished jumping");
        SetEntityState(Component::State::Entity::Idle);
    }
}

void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*entity_);
}
