#include "Game/World/src/block.h"

Block::Block() : block_object_(new sf::RectangleShape) {}

sf::RectangleShape* Block::Get()
{
    return block_object_.get();
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*block_object_);
}
