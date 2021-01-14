#include "Entities/src/player_entity.h"
#include <SFML/Graphics.hpp>

static int i{0};
static bool up{false};
static bool down{true};

sf::RectangleShape PlayerEntity::Update() {
    sf::RectangleShape shape;
    shape.setSize({200, 200});
    if (i == 1024 && down) {
        up = true;
        down = false;
    }

    if (i == 0 && up) {
        up = false;
        down = true;
    }

    up ? i-- : i++;

    shape.setPosition(200, i);
    shape.setFillColor(sf::Color::Green);
    return shape;
}
