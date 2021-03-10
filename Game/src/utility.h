#ifndef BLOCKJUMP_UTILITY_H
#define BLOCKJUMP_UTILITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>
#include <vector>

namespace Utility {
    bool AreObjectsColliding(const sf::RectangleShape &entity, const std::vector<sf::RectangleShape> &shapes) {
        return std::any_of(shapes.begin() + 1, shapes.end(), [&](const sf::RectangleShape &shape) {
            return shape.getGlobalBounds().intersects(entity.getGlobalBounds());
        });
    }
}

#endif //BLOCKJUMP_UTILITY_H
