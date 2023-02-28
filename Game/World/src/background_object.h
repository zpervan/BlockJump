#ifndef BLOCKJUMP_BACKGROUND_OBJECT_H
#define BLOCKJUMP_BACKGROUND_OBJECT_H

#include <SFML/Graphics.hpp>

/// @brief The main interface for all derived background objects
class BackgroundObject : public sf::Drawable
{
  public:
    virtual ~BackgroundObject() = default;
    virtual sf::RectangleShape* Get() = 0;
};

#endif  // BLOCKJUMP_BACKGROUND_OBJECT_H
