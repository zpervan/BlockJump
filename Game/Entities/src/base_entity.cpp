#include "Game/Entities/src/base_entity.h"

#include "Game/constants.h"

static const sf::Vector2f Max_Velocity{250.0f, 250.0f};

BaseEntity::BaseEntity(EntityManager* entity_manager) : entity_manager_(entity_manager) {}

/// @TODO: Once the friction component implemented, apply it to the velocity
void BaseEntity::AddVelocity(sf::Vector2f value)
{
    velocity_ += value;

    if (std::abs(velocity_.x) > Max_Velocity.x)
    {
        velocity_.x < 0 ? velocity_.x = -Max_Velocity.x : velocity_.x = Max_Velocity.x;
    }

    if (std::abs(velocity_.y) > Max_Velocity.y)
    {
        velocity_.y < 0 ? velocity_.y = -Max_Velocity.y : velocity_.y = Max_Velocity.y;
    }
}

void BaseEntity::SetVelocity(sf::Vector2f value)
{
    velocity_ = value;
}

sf::Vector2f BaseEntity::Velocity() const
{
    return velocity_;
}

sf::RectangleShape* BaseEntity::Get()
{
    return entity_.get();
}

void BaseEntity::Accelerate(sf::Vector2f value)
{
    acceleration_ += value;
}

void BaseEntity::SetAcceleration(sf::Vector2f value)
{
    acceleration_ = value;
}

sf::Vector2f BaseEntity::Acceleration() const
{
    return acceleration_;
}

void BaseEntity::SetEntityState(Component::State::Entity entity_state)
{
    entity_state_ = entity_state;
}

Component::State::Entity BaseEntity::EntityState() const
{
    return entity_state_;
}

sf::Vector2f BaseEntity::GetPositionToMove() const
{
    return position_to_move_;
}

Direction BaseEntity::GetDirection() const
{
    return direction_;
}

void BaseEntity::SetDirection(Direction direction)
{
    direction_ = direction;
}
