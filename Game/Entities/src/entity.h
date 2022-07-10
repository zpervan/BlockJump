#ifndef BLOCKJUMP_ENTITY_H
#define BLOCKJUMP_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

/// @brief Represents the base class for each entity created in the game.
class Entity
{
  public:
    void SetPosition(const sf::Vector2f& position);

    void SetRotation(float angle);

    void SetVelocity(float velocity);

    void SetTexture(const sf::Texture* texture);

    [[nodiscard]] const sf::Vector2f& GetPosition() const;

    [[nodiscard]] float GetRotation() const;

    [[nodiscard]] float GetVelocity() const;

    sf::RectangleShape* GetEntity();

    sf::Vector2f GetPositionToMove() const;

    void Update();

  protected:
    std::unique_ptr<sf::RectangleShape> entity_{std::make_unique<sf::RectangleShape>()};
    sf::Vector2f position_to_move_{0.0, 0.0};
    float velocity_{0.05};
};

#endif  // BLOCKJUMP_ENTITY_H
