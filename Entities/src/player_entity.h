#ifndef BLOCKJUMP_PLAYER_ENTITY_H
#define BLOCKJUMP_PLAYER_ENTITY_H

#include "Entities/src/entity.h"
#include <cstdint>
#include <SFML/Graphics/RectangleShape.hpp>

class PlayerEntity : public Entity {
public:
    sf::RectangleShape Update();

private:
//    uint8_t health{100};
};


#endif //BLOCKJUMP_PLAYER_ENTITY_H
