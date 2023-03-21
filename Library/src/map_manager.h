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
    bool Load(const std::string& path);

    /// @brief Saves the map data into a @c .map file.
    /// @param tiles Map tiles which will be serialized
    /// @return @c true if saving was successful, @c false otherwise
    /// @details Currently, this function is used in a different thread and that is why it's @c static and uses @c
    /// shared_ptr as a the function argument type.
    static bool Save(const std::vector<std::shared_ptr<Tile>>& tiles);

    /// @brief Fetches the map data related to the map background tiles.
    /// @return Vector of background tiles
    std::vector<sf::RectangleShape*>& BackgroundObjects();

    /// @brief Fetches the map data related to player entities.
    /// @return Player entities
    /// @todo Add NPC entities
    std::vector<sf::RectangleShape*>& GetPlayerEntities();

  private:
    std::vector<sf::RectangleShape*> background_objects_;
    std::vector<sf::RectangleShape*> player_entities_;
};

#endif  // BLOCKJUMP_MAP_MANAGER_H
