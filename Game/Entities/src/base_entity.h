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

    virtual void Move(float elapsed_time) = 0;
    virtual void Update(float elapsed_time) = 0;

    /// @brief Adds the passed velocity value to the current acceleration vector.
    /// @param value
    void Accelerate(sf::Vector2f value);

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

    bool Collision();

    sf::RectangleShape* Get();

  protected:
    EntityManager* entity_manager_;
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    Component::State::Entity entity_state_{Component::State::Entity::Idle};

    sf::FloatRect new_bounding_box_;
    sf::Vector2f current_position_{0.0f, 0.0f};
    sf::Vector2f position_to_move_{0.0f, 0.0f};
    sf::Vector2f velocity_{0.0f, 0.0f};
    sf::Vector2f acceleration_{0.0f, 0.0f};

    Direction direction_{Direction::None};
};

#endif  // BLOCKJUMP_BASE_ENTITY_H
