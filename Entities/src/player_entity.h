#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include "Entities/src/entity.h"
#include "SFML/Graphics/RectangleShape.hpp"

/// @brief Contains all the information about the player entity.
/// @verbatim
/// Those information are:
/// * Position (x,y)
/// * Orientation (angle in degrees)
/// @endverbatim
class PlayerEntity : public Entity
{
  public:
    /// @brief Updates the model state (position and orientation).
    /// @return The updated shape
    sf::RectangleShape UpdateState();

    void UpdatePosition();

    /// @brief Changes the position value w.r.t the pressed key.
    void Move(std::vector<sf::RectangleShape>& entities);

    sf::Vector2f GetPositionToMove() const;

  private:
    const std::size_t max_width_{1280};
    const std::size_t max_height_{1024};
    sf::RectangleShape player_entity_{};
    sf::Vector2f position_to_move_{0.0, 0.0};
};

#endif  // BLOCKJUMP_PLAYER_ENTITY_H
