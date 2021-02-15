#include "Entities/src/entity.h"

void Entity::SetPosition(const sf::Vector2f &position) {
    position_ = position;
}

void Entity::SetOrientation(const sf::Vector2f &orientation) {
    orientation_ = orientation;
}

const sf::Vector2f & Entity::GetPosition() const {
    return position_;
}

const sf::Vector2f & Entity::GetOrientation() const {
    return orientation_;
}

float Entity::GetVelocity() const {
    return velocity_;
}

void Entity::SetVelocity(float velocity) {
    Entity::velocity_ = velocity;
}
