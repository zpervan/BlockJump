#ifndef BLOCKJUMP_GROUND_H
#define BLOCKJUMP_GROUND_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace World {
    class Ground {
    public:
        sf::RectangleShape GenerateGround();

        void SetGroundPosition(sf::Vector2f ground_position);

        [[nodiscard]] sf::Vector2f GetGroundPosition();

    private:
        std::unique_ptr<sf::Vector2f> ground_position_{nullptr};
    };
}

#endif //BLOCKJUMP_GROUND_H
