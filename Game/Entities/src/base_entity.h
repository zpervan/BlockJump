#ifndef BLOCKJUMP_BASE_ENTITY_H
#define BLOCKJUMP_BASE_ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Game/Entities/src/entity_manager.h"

/// @brief Represents the base class for each entity created in the game.
class BaseEntity : public sf::Drawable
{
  public: /* Functions */
    explicit BaseEntity(EntityManager* entity_manager);

    virtual void Move() = 0;

    /// @brief Updates the entity pose and movement speed data.
    virtual void Update();

    sf::Vector2f GetPositionToMove() const;

    void SetVelocity(float velocity);
    float Velocity() const;

    void SetAcceleration(float acceleration);
    float Acceleration() const;

    void SetEntityState(Component::State::Entity entity_state);
    Component::State::Entity EntityState() const;

    sf::RectangleShape* Get();

  protected:
    EntityManager* entity_manager_;
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    Component::State::Entity entity_state_{Component::State::Entity::Idle};

    sf::Vector2f current_position_{0.0f, 0.0f};
    sf::Vector2f position_to_move_{0.0f, 0.0f};
    float velocity_{0.15f};
    float acceleration_{0.0f};
};

#endif  // BLOCKJUMP_BASE_ENTITY_H
