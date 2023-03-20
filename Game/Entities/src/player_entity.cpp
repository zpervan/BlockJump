#include "Game/Entities/src/player_entity.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "Game/constants.h"

constexpr float acceleration_tick{0.2f};
static const sf::Vector2f Zero_Vector{0.0f, 0.0f};
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
    switch (direction_)
    {
        case Direction::None:
        case Direction::Up:
            SetAcceleration({0, 0});
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

        default:
            break;
    }

    // While floating, add the gravitational component to the acceleration
    Accelerate({0.0f, Constants::GRAVITY});

    AddVelocity(acceleration_);

    position_to_move_ = entity_->getPosition() + (velocity_ * elapsed_time);
}

void PlayerEntity::Jump()
{
    /// @TODO: Implement jumping
}

void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*entity_);
}
