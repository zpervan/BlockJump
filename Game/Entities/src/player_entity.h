#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include "Game/Entities/src/entity.h"
#include "Game/World/src/background_object.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

/// @brief Contains all the information about the player entity.
/// @verbatim
/// Those information are:
/// * Position (x,y)
/// * Orientation (angle in degrees)
/// @endverbatim
class PlayerEntity : public Entity
{
  public:
    explicit PlayerEntity(sf::Vector2f startingPosition);

    /// @brief Changes the position value w.r.t the pressed key.
    void Move(std::vector<BackgroundObject*>& entities);

  private:
    void Jump(std::vector<BackgroundObject*>& entities);

    sf::Clock jumping_clock_{};
    sf::Time jumping_timer_{};
    float jumping_timer_delta_{0.0f};
};

#endif  // BLOCKJUMP_PLAYER_ENTITY_H
