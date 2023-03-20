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

void BaseEntity::CheckCollision()
{
    const float old_x_left = entity_->getPosition().x;
    const float old_x_right = entity_->getPosition().x + entity_->getSize().x;
    const float old_y_top = entity_->getPosition().y;
    const float old_y_bottom = entity_->getPosition().y + entity_->getSize().y;

    const float new_x_left = position_to_move_.x;
    const float new_x_right = position_to_move_.x + entity_->getSize().x;
    const float new_y_top = position_to_move_.y;
    const float new_y_bottom = position_to_move_.y + entity_->getSize().y;

    auto* collidable = entity_manager_->GetComponent<Component::Collidable>(id_);
    collidable->Reset();

    for (const auto& entity : entity_manager_->GetEntities())
    {
        // Skip checking the same entities
        if (entity.first == id_)
        {
            continue;
        }

        if (!entity.second->shape.getGlobalBounds().intersects({position_to_move_, entity_->getSize()}))
        {
            continue;
        }

        const auto& entity_bounds = entity.second->shape.getGlobalBounds();

        if (entity_bounds.contains(new_x_left, old_y_top) || entity_bounds.contains(new_x_left, old_y_bottom))
        {
            collidable->x_left_collision = true;
        }

        if (entity_bounds.contains(new_x_right, old_y_top) || entity_bounds.contains(new_x_right, old_y_bottom))
        {
            collidable->x_right_collision = true;
        }

        if (entity_bounds.contains(old_x_left, new_y_top) || entity_bounds.contains(old_x_right, new_y_top))
        {
            collidable->y_top_collision = true;
        }

        if (entity_bounds.contains(old_x_left, new_y_bottom) || entity_bounds.contains(old_x_right, new_y_bottom))
        {
            collidable->y_bottom_collision = true;
        }
    }
}

void BaseEntity::HandleCollision()
{
    const auto collidable = entity_manager_->GetComponent<Component::Collidable>(id_);

    if (collidable->x_left_collision || collidable->x_right_collision)
    {
        SetAcceleration({0.0f, acceleration_.y});
        SetVelocity({0.0f, velocity_.y});
        position_to_move_.x = entity_->getPosition().x;
    }

    if (collidable->y_top_collision || collidable->y_bottom_collision)
    {
        SetAcceleration({acceleration_.x, 0.0f});
        SetVelocity({velocity_.x, 0.0f});
        position_to_move_.y = entity_->getPosition().y;
    }
}
