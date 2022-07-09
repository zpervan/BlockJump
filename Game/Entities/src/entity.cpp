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
