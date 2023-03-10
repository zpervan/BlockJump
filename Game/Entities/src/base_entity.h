#ifndef BLOCKJUMP_BASE_ENTITY_H
#define BLOCKJUMP_BASE_ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Game/Entities/src/entity_manager.h"

enum class EntityState
{
    Idle = 0,
    Moving,
    Jumping,
    Dead
};

/// @brief Represents the base class for each entity created in the game.
class BaseEntity : public sf::Drawable
{
  public: /* Functions */
    explicit BaseEntity(EntityManager* entity_manager);

    /// @brief Updates the entity pose and movement speed data.
    void Update();

    void Move(sf::Vector2f position_to_move);
    sf::Vector2f GetPositionToMove() const;

    void SetVelocity(float velocity);
    float GetVelocity() const;

    float GetAcceleration() const;
    void SetAcceleration(float acceleration);

    void SetEntityState(EntityState entity_state);
    EntityState GetEntityState() const;

    sf::RectangleShape* Get();

  protected:
    EntityManager* entity_manager_;
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    EntityState entity_state_{EntityState::Idle};

    sf::Vector2f current_position_{0.0f, 0.0f};
    sf::Vector2f position_to_move_{0.0f, 0.0f};
    float velocity_{0.05f};
    float acceleration_{0.0f};
};

#endif  // BLOCKJUMP_BASE_ENTITY_H
