#ifndef BLOCKJUMP_ENTITY_H
#define BLOCKJUMP_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

enum class EntityState
{
    NoAction = 0,
    Moving,
    Jumping,
    Dead
};

/// @brief Represents the base class for each entity created in the game.
class BaseEntity : public sf::Drawable
{
  public: /* Functions */
    /// @brief Updates the entity pose and movement speed data.
    void Update();

    void SetEntityState(EntityState entity_state);
    float GetVelocity() const;
    sf::Vector2f GetPositionToMove() const;
    EntityState GetEntityState() const;

    sf::RectangleShape* Get();

  protected:
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    sf::Vector2f position_to_move_{0.0, 0.0};
    EntityState entity_state_{EntityState::NoAction};
    float velocity_{0.05};
};

#endif  // BLOCKJUMP_ENTITY_H
