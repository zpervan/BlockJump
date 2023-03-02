#ifndef BLOCKJUMP_MAP_MANAGER_H
#define BLOCKJUMP_MAP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

class MapManager
{
  public:
    ~MapManager();

    /// @brief Loads the map on a given path.
    /// @param path Path to the map file
    bool Load(std::string path);

    /// @brief Fetches the map data which contains map background tiles.
    /// @return Vector of background tiles
    /// @todo Extend to NPC and player drawables
    std::vector<sf::RectangleShape*>& BackgroundObjects();

  private:
    std::vector<sf::RectangleShape*> background_objects_;
};

#endif  // BLOCKJUMP_MAP_MANAGER_H
