#ifndef BLOCKJUMP_UTILITY_H
#define BLOCKJUMP_UTILITY_H

#include <algorithm>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <spdlog/spdlog.h>

namespace Utility
{

// @TODO: Calculate this from the entity velocity
constexpr float POSITION_OFFSET{1.0};

bool IsColliding(const sf::RectangleShape& entity, const std::vector<sf::RectangleShape>& entities, sf::Keyboard::Key key)
{
    for (const auto& e : entities)
    {
        // Skip the processed entity
        if (e.getGlobalBounds() == entity.getGlobalBounds())
        {
            continue;
        }

        // Add some offset in order to check whether our next move would collide with an existing entity
        sf::FloatRect new_entity_position = entity.getGlobalBounds();

        switch (key)
        {
            case sf::Keyboard::Key::Left:
                new_entity_position.left -= POSITION_OFFSET;
                break;

            case sf::Keyboard::Key::Right:
                new_entity_position.width += POSITION_OFFSET;
                break;

            case sf::Keyboard::Key::Up:
                new_entity_position.top -= POSITION_OFFSET;
                break;

            case sf::Keyboard::Key::Down:
                new_entity_position.height += POSITION_OFFSET;
                break;

            default:
                break;
        }

        if (e.getGlobalBounds().intersects(new_entity_position))
        {
            return true;
        }
    }

    return false;
}
}  // namespace Utility

#endif  // BLOCKJUMP_UTILITY_H
