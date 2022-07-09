#ifndef BLOCKJUMP_BLOCK_H
#define BLOCKJUMP_BLOCK_H

#include "Game/World/src/background_object.h"

#include <memory>

class Block : public BackgroundObject
{
  public:
    Block();
    ~Block() override = default;

    void SetSize(sf::Vector2f size) override;
    void SetPosition(sf::Vector2f position) override;
    void SetRotation(float angle) override;
    void SetTexture(const sf::Texture* texture) override;
    void SetFillColor(sf::Color color) override;

    sf::RectangleShape * Get() override;

  private:
    std::unique_ptr<sf::RectangleShape> block_object_;
};

#endif  // BLOCKJUMP_BLOCK_H
