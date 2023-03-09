#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>

#include "Game/Entities/src/base_entity.h"

/// @brief Contains all the information about the player entity.
/// @verbatim
/// Those information are:
/// * Position (x,y)
/// * Orientation (angle in degrees)
/// @endverbatim
class PlayerEntity : public BaseEntity
{
  public:
    PlayerEntity();
    explicit PlayerEntity(sf::Vector2f startingPosition);

    /// @brief Changes the position value w.r.t the pressed key.
    void Move(std::vector<sf::RectangleShape*>& entities);

  private: /* Functions */
    void Jump(std::vector<sf::RectangleShape*>& entities);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private: /* Data members */
    sf::Clock jumping_clock_;
    sf::Time jumping_timer_;
    float jumping_timer_delta_{0.0f};
};

#endif  // BLOCKJUMP_PLAYER_ENTITY_H
