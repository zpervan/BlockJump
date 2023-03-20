#ifndef BLOCKJUMP_BASE_ENTITY_H
#define BLOCKJUMP_BASE_ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Game/Entities/src/entity_manager.h"

enum class Direction
{
    None = 0,
    Up,
    Down,
    Left,
    Right
};

/// @brief Represents the base class for each entity created in the game.
class BaseEntity : public sf::Drawable
{
  public: /* Functions */
    explicit BaseEntity(EntityManager* entity_manager);

    /// @brief Updates all related data for the entity.
    /// @param elapsed_time How much time has passed since the last update
    virtual void Update(float elapsed_time) = 0;

    /// @brief Moves the entity based on the current velocity and elapsed time in the direction of the pressed arrow key.
    /// @param elapsed_time How much time has passed since the last update
    virtual void Move(float elapsed_time) = 0;

    /// @brief Adds the passed velocity value to the current acceleration vector.
    /// @param value Vector value
    void Accelerate(sf::Vector2f value);

    /// @brief Checks and handles situation where a collision is detected.
    void CheckCollision();

    /// @brief Handles collision situations by handling acceleration, speed and position data.
    void HandleCollision();

    /* Getters and setters */
    sf::Vector2f GetPositionToMove() const;

    sf::Vector2f Velocity() const;
    void AddVelocity(sf::Vector2f value);
    void SetVelocity(sf::Vector2f value);

    sf::Vector2f Acceleration() const;
    void SetAcceleration(sf::Vector2f value);

    Direction GetDirection() const;
    void SetDirection(Direction direction);

    void SetEntityState(Component::State::Entity entity_state);
    Component::State::Entity EntityState() const;

    EntityId Id() const;
    void SetId(EntityId id);

    sf::RectangleShape* Get();

  protected:
    EntityId id_;
    EntityManager* entity_manager_;
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    Component::State::Entity entity_state_{Component::State::Entity::Idle};

    sf::Vector2f position_to_move_{0.0f, 0.0f};
    sf::Vector2f velocity_{0.0f, 0.0f};
    sf::Vector2f acceleration_{0.0f, 0.0f};

    Direction direction_{Direction::None};
};

#endif  // BLOCKJUMP_BASE_ENTITY_H
