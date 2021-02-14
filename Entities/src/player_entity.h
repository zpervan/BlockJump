#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include "Entities/src/entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PlayerEntity : public Entity {
public:
    sf::RectangleShape Update();

    void Move();

private:
    const std::size_t max_width_{1280};
    const std::size_t max_height_{1024};
};


#endif //BLOCKJUMP_PLAYER_ENTITY_H
