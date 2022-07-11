#ifndef BLOCKJUMP_UTILITY_H
#define BLOCKJUMP_UTILITY_H

#include "Game/World/src/background_object.h"
#include "Game/Entities/src/entity.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <spdlog/spdlog.h>

#include <vector>

namespace Utility
{

// @TODO: Consider to use the intersect function in order to calculate collision
bool IsColliding(Entity & entity, const std::vector<BackgroundObject*>& entities)
{
    for (const auto& e : entities)
    {
        // Upper left point
        if(e->Get()->getGlobalBounds().contains(entity.GetPositionToMove().x, entity.GetPositionToMove().y))
        {
            return true;
        }

        // Upper right point
        if(e->Get()->getGlobalBounds().contains(entity.GetPositionToMove().x + entity.GetEntity()->getSize().x, entity.GetPositionToMove().y))
        {
            return true;
        }
        // Lower right point
        if(e->Get()->getGlobalBounds().contains(entity.GetPositionToMove().x + entity.GetEntity()->getSize().x, entity.GetPositionToMove().y + entity.GetEntity()->getSize().y))
        {
            return true;
        }

        // Lower left point
        if(e->Get()->getGlobalBounds().contains(entity.GetPositionToMove().x, entity.GetPositionToMove().y + entity.GetEntity()->getSize().y))
        {
            return true;
        }
    }

    return false;
}
}  // namespace Utility

#endif  // BLOCKJUMP_UTILITY_H
