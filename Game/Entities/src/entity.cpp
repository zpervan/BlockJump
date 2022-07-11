#include "Game/Entities/src/entity.h"

void Entity::SetPosition(const sf::Vector2f& position)
{
    entity_->setPosition(position);
}

void Entity::SetRotation(float angle)
{
    entity_->setRotation(angle);
}

const sf::Vector2f& Entity::GetPosition() const
{
    return entity_->getPosition();
}

float Entity::GetRotation() const
{
    return entity_->getRotation();
}

float Entity::GetVelocity() const
{
    return velocity_;
}

void Entity::SetVelocity(float velocity)
{
    Entity::velocity_ = velocity;
}

void Entity::SetTexture(const sf::Texture* texture)
{
    entity_->setTexture(texture);
}

sf::RectangleShape* Entity::GetEntity()
{
    return entity_.get();
}

sf::Vector2f Entity::GetPositionToMove() const
{
    return position_to_move_;
}

void Entity::Update()
{
    entity_->setPosition(position_to_move_);
}

EntityState Entity::GetEntityState() const
{
    return entity_state_;
}

void Entity::SetEntityState(EntityState entity_state)
{
    entity_state_ = entity_state;
}
