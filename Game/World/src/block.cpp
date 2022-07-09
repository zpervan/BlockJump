#include "Game/World/src/block.h"

Block::Block() : block_object_(new sf::RectangleShape) {}

void Block::SetSize(sf::Vector2f size)
{
    block_object_->setSize(size);
}

void Block::SetPosition(sf::Vector2f position)
{
    block_object_->setPosition(position);
}

void Block::SetRotation(float angle)
{
    block_object_->setRotation(angle);
}

void Block::SetTexture(const sf::Texture* texture)
{
    block_object_->setTexture(texture);
}

void Block::SetFillColor(sf::Color color)
{
    block_object_->setFillColor(color);
}

sf::RectangleShape* Block::Get()
{
    return block_object_.get();
}
