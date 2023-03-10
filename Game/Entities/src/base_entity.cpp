#include "Game/Entities/src/base_entity.h"

BaseEntity::BaseEntity(EntityManager* entity_manager) : entity_manager_(entity_manager) {}

void BaseEntity::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

float BaseEntity::GetVelocity() const
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
    entity_->setPosition(position_to_move_);
}

EntityState BaseEntity::GetEntityState() const
{
    return entity_state_;
}

void BaseEntity::SetEntityState(EntityState entity_state)
{
    entity_state_ = entity_state;
}

float BaseEntity::GetAcceleration() const
{
    return acceleration_;
}

void BaseEntity::SetAcceleration(float acceleration)
{
    acceleration_ = acceleration;
}

void BaseEntity::Move(sf::Vector2f position_to_move)
{
    position_to_move_ = position_to_move;
}
