#ifndef BLOCKJUMP_GAME_H
#define BLOCKJUMP_GAME_H

#include "ThirdParty/SFML/include/SFML/Graphics.hpp"
#include "ThirdParty/SFML/include/SFML/OpenGL.hpp"

#include "Entities/src/player_entity.h"
#include "World/src/ground.h"

#include <vector>
/// @brief Manages the lifetime and screen content of the game window.
class Game {
public:
    void Initialize();

    /// @brief Updates the content of the game screen space.
    void Run();

private:
    void ProcessEvents();

    void Update();

    void Display();

    void ShowEntities();

    sf::RenderWindow window_{sf::VideoMode(1280, 1024), "Block game"};
    PlayerEntity player_entity_;
    World::Ground ground_;
    std::vector<sf::RectangleShape> rectangle_shapes_;
};

#endif  // BLOCKJUMP_GAME_H
