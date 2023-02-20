#include "Game/Entities/src/base_entity.h"

void BaseEntity::SetPosition(const sf::Vector2f& position)
{
    entity_->setPosition(position);
}

void BaseEntity::SetRotation(float angle)
{
    entity_->setRotation(angle);
}

const sf::Vector2f& BaseEntity::GetPosition() const
{
    return entity_->getPosition();
}

float BaseEntity::GetRotation() const
{
    return entity_->getRotation();
}

float BaseEntity::GetVelocity() const
{
    return velocity_;
}

void BaseEntity::SetVelocity(float velocity)
{
    BaseEntity::velocity_ = velocity;
}

void BaseEntity::SetTexture(const sf::Texture* texture)
{
    entity_->setTexture(texture);
}

sf::RectangleShape* BaseEntity::GetEntity()
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
