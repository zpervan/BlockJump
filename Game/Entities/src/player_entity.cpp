#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/constants.h"

constexpr float acceleration_tick{0.2f};
constexpr float deceleration_tick{2.0f};
static const sf::Vector2f Default_Player_Size{40.0f, 40.0f};

PlayerEntity::PlayerEntity(EntityManager* entity_manager) : BaseEntity(entity_manager)
{
    spdlog::debug("Creating player entity");
    entity_->setSize(Default_Player_Size);
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
    CheckCollision();
    HandleCollision();

    entity_->setPosition(position_to_move_);
}

void PlayerEntity::Move(float elapsed_time)
{
    const auto collidable = entity_manager_->GetComponent<Component::Collidable>(id_);

    // While floating, add the gravitational component to the acceleration if there is no collision detected
    if (!collidable->y_bottom_collision)
    {
        Accelerate({0.0f, Constants::GRAVITY});
    }

    if (entity_state_ == Component::State::Entity::JumpStart)
    {
        Jump();
    }

    if ((entity_state_ == Component::State::Entity::Jumping) && (collidable->y_bottom_collision))
    {
        entity_state_ = Component::State::Entity::Idle;
    }

    switch (direction_)
    {
        case Direction::None:
            SetAcceleration({0.0f, acceleration_.y});
            /// @TODO: Reduce the velocity slowly so we have a more smooth slowing animation
            SetVelocity({0.0f, 0.0f});
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

        case Direction::Up:
        default:
            break;
    }

    AddVelocity(acceleration_);

    position_to_move_ = entity_->getPosition() + (velocity_ * elapsed_time);
}

void PlayerEntity::Jump()
{
    Accelerate({0.0f, -300.0f});
    entity_state_ = Component::State::Entity::Jumping;
}

void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*entity_);
}
