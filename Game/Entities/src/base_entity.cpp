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

EntityId BaseEntity::Id() const
{
    return id_;
}

void BaseEntity::SetId(EntityId id)
{
    id_ = id;
}

/// @TODO: Extract collision handling in a separate function?
bool BaseEntity::Collision()
{
    const float entity_x_left = position_to_move_.x;
    const float entity_x_right = position_to_move_.x + entity_->getSize().x;
    const float entity_y_top = position_to_move_.y;
    const float entity_y_bottom = position_to_move_.y + entity_->getSize().y;

    for (const auto& entity : entity_manager_->GetEntities())
    {
        // Skip checking the same entities
        if (entity.first == id_)
        {
            continue;
        }

        const auto& other_entity_global_bounds = entity.second->shape.getGlobalBounds();
        if (!other_entity_global_bounds.intersects({position_to_move_, entity_->getSize()}))
        {
            continue;
        }

        // X-component collision
        const float other_entity_x_right = other_entity_global_bounds.left + other_entity_global_bounds.width;
        if ((entity_x_right >= other_entity_global_bounds.left) && (entity_x_left <= other_entity_x_right))
        {
            SetAcceleration({0.0f, acceleration_.y});
            SetVelocity({0.0f, velocity_.y});
        }

        // Y-component collision
        const float other_entity_y_bottom = other_entity_global_bounds.top + other_entity_global_bounds.height;
        if ((entity_y_bottom >= other_entity_global_bounds.top) && (entity_y_top <= other_entity_y_bottom))
        {
            SetAcceleration({acceleration_.x, 0.0f});
            SetVelocity({velocity_.x, 0.0f});
        }

        return true;
    }

    return false;
}
