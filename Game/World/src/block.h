#ifndef BLOCKJUMP_BLOCK_H
#define BLOCKJUMP_BLOCK_H

#include <memory>

#include "Game/World/src/background_object.h"

class Block : public BackgroundObject
{
  public:
    Block();
    ~Block() override = default;

    sf::RectangleShape* Get() override;

  private: /* Functions */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private: /* Data members */
    std::unique_ptr<sf::RectangleShape> block_object_;
};

#endif  // BLOCKJUMP_BLOCK_H
