#include "Game/Entities/src/base_entity.h"

BaseEntity::BaseEntity(EntityManager* entity_manager) : entity_manager_(entity_manager) {}

void BaseEntity::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

float BaseEntity::Velocity() const
{
    return velocity_;
}

sf::RectangleShape* BaseEntity::Get()
{
    return entity_.get();
}

sf::Vector2f BaseEntity::GetPositionToMove() const
{
    return position_to_move_;
}

void BaseEntity::Update()
{
    // Suggested workflow:
    // Calculate acceleration
    // Calculate velocity
    // Apply tile friction
    // Move entity
    // Check for collisions

    Move();
    entity_->setPosition(position_to_move_);
}

Component::State::Entity BaseEntity::EntityState() const
{
    return entity_state_;
}

void BaseEntity::SetEntityState(Component::State::Entity entity_state)
{
    entity_state_ = entity_state;
}

float BaseEntity::Acceleration() const
{
    return acceleration_;
}

void BaseEntity::SetAcceleration(float acceleration)
{
    acceleration_ = acceleration;
}
