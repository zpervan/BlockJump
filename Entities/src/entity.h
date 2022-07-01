#ifndef BLOCKJUMP_ENTITY_H
#define BLOCKJUMP_ENTITY_H

#include "SFML/System/Vector2.hpp"

/// @brief Represents the base class for each object located in the game.
class Entity {
public:
    void SetPosition(const sf::Vector2f &position);

    void SetOrientation(const sf::Vector2f &orientation);

    void SetVelocity(float velocity);

    [[nodiscard]] const sf::Vector2f &GetPosition() const;

    [[nodiscard]] const sf::Vector2f &GetOrientation() const;

    [[nodiscard]] float GetVelocity() const;

protected:
    sf::Vector2f position_{50, 800};
    sf::Vector2f orientation_{0, 0};
    float velocity_{1.0};
};

#endif //BLOCKJUMP_ENTITY_H
