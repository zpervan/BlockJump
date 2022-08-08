#ifndef BLOCKJUMP_MAP_SERIALIZATION_H
#define BLOCKJUMP_MAP_SERIALIZATION_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

/// @TODO: Refactor in order to avoid using tiles service for data type
#include "MapEditor/Map/src/tiles_service.h"

class MapSerialization
{
  public:
    static bool Serialize(const std::vector<std::shared_ptr<Tile>>&  map_tiles);
    static std::vector<sf::RectangleShape> Deserialize();
};

#endif  // BLOCKJUMP_MAP_SERIALIZATION_H
