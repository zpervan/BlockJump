#include "World/src/ground.h"

#include <stdexcept>

sf::RectangleShape World::Ground::GenerateGround() {
    if (ground_position_ == nullptr) {
        throw std::invalid_argument("Ground position not set!");
    }

    sf::RectangleShape ground;
    ground.setFillColor(sf::Color::Black);
    ground.setPosition(*ground_position_);
    ground.setSize({1280.0, 50.0});
    return ground;
}

void World::Ground::SetGroundPosition(sf::Vector2f ground_position) {
    ground_position_ = std::make_unique<sf::Vector2f>(ground_position);
}

sf::Vector2f World::Ground::GetGroundPosition() {
    return *ground_position_;
}
