#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/World/src/utility.h"
#include "Game/constants.h"

constexpr float acceleration_tick{0.2f};

PlayerEntity::PlayerEntity(EntityManager* entity_manager) : BaseEntity(entity_manager)
{
    spdlog::debug("Creating player entity");
    entity_->setSize({50.0f, 50.0f});
}

void PlayerEntity::Update(float elapsed_time)
{
    // Suggested workflow:
    // Calculate acceleration
    // Calculate velocity
    // Apply tile friction
    // Move entity
    // Check for collisions
    // Resolve collisions

    Move(elapsed_time);

    if (!Utility::IsColliding({entity_->getPosition(), entity_->getSize()}, entity_manager_->GetEntities()))
    {
        Accelerate({0.0f, Constants::GRAVITY});
        AddVelocity({acceleration_.x * elapsed_time, acceleration_.y * elapsed_time});
    }
    else
    {
        SetAcceleration({0.0f, 0.0f});
        SetVelocity({velocity_.x, 0.0f});
    }

    entity_->setPosition(position_to_move_);
}

void PlayerEntity::Move(float elapsed_time)
{
    switch (direction_)
    {
        case Direction::None:
            SetAcceleration({0, 0});
            break;

        case Direction::Down:
            Accelerate({0.0f, acceleration_tick});
            break;

        case Direction::Left:
            Accelerate({-acceleration_tick, 0.0f});
            break;

        case Direction::Right:
            Accelerate({acceleration_tick, 0.0f});
            break;

        default:
            break;
    }

    if (acceleration_ != sf::Vector2f{0.0f, 0.0f})
    {
        AddVelocity(acceleration_);
    }
    else
    {
        SetVelocity({0.0f, 0.0f});
    }

    position_to_move_ = entity_->getPosition() + (velocity_ * elapsed_time);
}

void PlayerEntity::Jump()
{
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (EntityState() != Component::State::Entity::Jumping))
    //    {
    //        spdlog::debug("Initiating jumping");
    //        jumping_timer_delta_ = 0.0f;
    //        jumping_timer_ = jumping_clock_.getElapsedTime();
    //        SetEntityState(Component::State::Entity::Jumping);
    //    }
    //
    //    const sf::Vector2f ground_position{position_to_move_.x, position_to_move_.y + Velocity()};
    //    const sf::Vector2f up_position{position_to_move_.x, position_to_move_.y - Velocity()};
    //
    //    if ((EntityState() == Component::State::Entity::Jumping) &&
    //        !Utility::IsColliding({up_position, entity_->getSize()}, entity_manager_->GetEntities()) &&
    //        jumping_timer_delta_ <= 0.2f)
    //    {
    //        jumping_timer_delta_ = jumping_clock_.getElapsedTime().asSeconds() - jumping_timer_.asSeconds();
    //        position_to_move_.y -= -powf(jumping_timer_delta_ / 10.0f, 3.0f) + (jumping_timer_delta_ / 10.0f) +
    //        0.075f;
    //    }
    //    else if ((EntityState() == Component::State::Entity::Jumping) &&
    //             Utility::IsColliding({ground_position, entity_->getSize()}, entity_manager_->GetEntities()))
    //    {
    //        spdlog::debug("Finished jumping");
    //        SetEntityState(Component::State::Entity::Idle);
    //    }
}

void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*entity_);
}
