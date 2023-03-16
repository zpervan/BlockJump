#include "Game/Entities/src/base_entity.h"

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

bool BaseEntity::Collision()
{
    new_bounding_box_ = sf::FloatRect{position_to_move_, entity_->getSize()};

    for (const auto& entity : entity_manager_->GetEntities())
    {
        // Skip checking the same entities
        if (entity.first == id_)
        {
            continue;
        }

        const auto& other_entity_global_bounds = entity.second->shape.getGlobalBounds();
        if (!other_entity_global_bounds.intersects(new_bounding_box_))
        {
            continue;
        }

        // X-component collision
        if ((new_bounding_box_.left + new_bounding_box_.width >= other_entity_global_bounds.left) ||
            (other_entity_global_bounds.left + other_entity_global_bounds.width >= new_bounding_box_.left))
        {
            SetAcceleration({0.0f, acceleration_.y});
            SetVelocity({0.0f, velocity_.y});
        }

        // Y-component collision
        if ((new_bounding_box_.top + new_bounding_box_.height >= other_entity_global_bounds.top) ||
            (other_entity_global_bounds.top + other_entity_global_bounds.height >= new_bounding_box_.top))
        {
            SetAcceleration({acceleration_.x, 0.0f});
            SetVelocity({velocity_.x, 0.0f});
        }

        return true;
    }

    return false;
}
