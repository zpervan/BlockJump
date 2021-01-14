#ifndef BLOCKJUMP_ENTITY_H
#define BLOCKJUMP_ENTITY_H

#include <SFML/System/Vector2.hpp>

/// @brief Represents the base class for each object located in the game.
class Entity {
public:
    void SetPosition(const sf::Vector2i &position);

    void SetOrientation(const sf::Vector2i &orientation);

    [[nodiscard]] const sf::Vector2i &GetPosition() const;

    [[nodiscard]] const sf::Vector2i &GetOrientation() const;

protected:
    sf::Vector2i position_{0, 0};
    sf::Vector2i orientation_{0, 0};
};

#endif //BLOCKJUMP_ENTITY_H
