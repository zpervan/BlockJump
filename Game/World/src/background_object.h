#ifndef BLOCKJUMP_BACKGROUND_OBJECT_H
#define BLOCKJUMP_BACKGROUND_OBJECT_H

#include <SFML/Graphics.hpp>

/// @brief Interface for all background objects
class BackgroundObject
{
  public:
    virtual ~BackgroundObject() = default;

    virtual void SetSize(sf::Vector2f size) = 0;
    virtual void SetPosition(sf::Vector2f position) = 0;
    virtual void SetRotation(float angle) = 0;
    virtual void SetTexture(const sf::Texture* texture) = 0;
    virtual void SetFillColor(sf::Color color) = 0;

    /// @TODO: Create more generic return type - template or sf::drawable?
    virtual sf::RectangleShape* Get() = 0;
};

#endif  // BLOCKJUMP_BACKGROUND_OBJECT_H
