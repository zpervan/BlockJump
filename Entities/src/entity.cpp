#include "Entities/src/entity.h"

void Entity::SetPosition(const sf::Vector2i &position) {
    position_ = position;
}

void Entity::SetOrientation(const sf::Vector2i &orientation) {
    orientation_ = orientation;
}

const sf::Vector2i &Entity::GetPosition() const {
    return position_;
}

const sf::Vector2i &Entity::GetOrientation() const {
    return orientation_;
}
