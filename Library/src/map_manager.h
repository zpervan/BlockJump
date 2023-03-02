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

    /// @brief Fetches the map data which is currently loaded
    /// @return Vector of drawables which represent the map tiles
    std::vector<sf::Drawable*>& Data();

  private:
    std::vector<sf::Drawable*> map_data_;
};

#endif  // BLOCKJUMP_MAP_MANAGER_H
