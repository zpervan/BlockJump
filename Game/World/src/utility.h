#ifndef BLOCKJUMP_UTILITY_H
#define BLOCKJUMP_UTILITY_H

#include "Game/Entities/src/base_entity.h"
#include "Game/World/src/background_object.h"

namespace Utility
{

inline bool IsColliding(sf::FloatRect entity_bounds, const std::vector<BackgroundObject*>& entities)
{
    return std::any_of(entities.begin(), entities.end(), [entity_bounds](auto& e) {
        return e->Get()->getGlobalBounds().intersects(entity_bounds);
    });
}

}  // namespace Utility

#endif  // BLOCKJUMP_UTILITY_H
