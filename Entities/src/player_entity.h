#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include "Entities/src/entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

/// @brief Contains all the information about the player entity.
/// @verbatim
/// Those information are:
/// * Position (x,y)
/// * Orientation (angle in degrees)
/// @endverbatim
class PlayerEntity : public Entity {
public:

    /// @brief Updates the model state (position and orientation).
    /// @return The updated shape
    sf::RectangleShape Update();

    /// @brief Changes the position value w.r.t to the pressed key.
    void Move();

private:
    const std::size_t max_width_{1280};
    const std::size_t max_height_{1024};
};


#endif //BLOCKJUMP_PLAYER_ENTITY_H
