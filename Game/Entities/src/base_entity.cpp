#include "Game/Entities/src/base_entity.h"

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
