#ifndef BLOCKJUMP_MAP_MANAGER_H
#define BLOCKJUMP_MAP_MANAGER_H

#include <vector>

#include "Library/src/assets_manager.h"
#include "Library/src/tiles.h"

class MapManager
{
  public:
    ~MapManager();

    /// @brief Loads the map on a given path.
    /// @param path Path to the map file
    /// @return @c true if loading was successful, @c false otherwise
    bool Load(std::string path);

    /// @brief Saves the map data into a @c .map file.
    /// @param tiles Map tiles which will be serialized
    /// @return @c true if saving was successful, @c false otherwise
    /// @details Currently, this function is used in a different thread and that is why it's @c static and uses @c
    /// shared_ptr as a the function argument type.
    static bool Save(const std::vector<std::shared_ptr<Tile>>& tiles);

    /// @brief Fetches the map data which contains map background tiles.
    /// @return Vector of background tiles
    /// @todo Extend to NPC and player drawables
    std::vector<sf::RectangleShape*>& BackgroundObjects();

  private:
    std::vector<sf::RectangleShape*> background_objects_;
};

#endif  // BLOCKJUMP_MAP_MANAGER_H
