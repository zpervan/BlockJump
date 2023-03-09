#include "Library/src/map_manager.h"

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>

#include "Library/src/assets_manager.h"
#include "Library/src/paths.h"
#include "ProtoMessages/map/map.pb.h"

bool MapManager::Load(std::string path)
{
    spdlog::info("Loading map");

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (!background_objects_.empty())
    {
        background_objects_.clear();
    }

    MapMessages::Map map;

    {
        // @TODO: Once the start game menu is implemented, make the path customizable
        // @TODO: Check if the file exists
        // @TODO: There is an error while saving the map by using the paths functionality
        std::fstream map_file{Paths::MapsDirectoryPath() + "single_player_test.map", std::ios::in | std::ios::binary};

        if (!map.ParseFromIstream(&map_file))
        {
            spdlog::error("Failed to load map!");
            return false;
        }

        map_file.close();
    }

    background_objects_.reserve(map.tiles_size());

    for (auto& tile : map.tiles())
    {
        auto* drawable = new sf::RectangleShape();
        drawable->setPosition(tile.position().x(), tile.position().y());
        drawable->setSize({64.0f, 64.0f});
        drawable->setTexture(AssetsManager::GetTexture(tile_proto_to_asset_type[tile.type()]));

        if (tile.type() == MapMessages::TileType::TILE_TYPE_PLAYER)
        {
            player_entities_.emplace_back(drawable);
        }
        else
        {
            background_objects_.emplace_back(drawable);
        }
    }

    spdlog::info("Map loaded successfully");

    return true;
}

bool MapManager::Save(const std::vector<std::shared_ptr<Tile>>& tiles)
{
    if (tiles.empty())
    {
        spdlog::warn("No map tiles to save. Canceling saving process.");
        return false;
    }

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    MapMessages::Map map;

    for (const auto& tile : tiles)
    {
        spdlog::debug("Adding tile of type {} on position {} {}",
                      tile_asset_type_to_string[tile->second],
                      tile->first.getPosition().x,
                      tile->first.getPosition().y);

        auto* proto_tile = map.add_tiles();
        proto_tile->set_type(tile_asset_type_to_proto[tile->second]);
        proto_tile->mutable_position()->set_x(tile->first.getPosition().x);
        proto_tile->mutable_position()->set_y(tile->first.getPosition().y);
    }

    /// @TODO: Consider to make the maps saving directory customizable, i.e. the user can set a custom save path
    //  std::fstream outfile{Paths::MapsDirectoryPath() + "example.map", std::ios::out | std::ios::trunc | std::ios::binary};
    std::fstream outfile{"/home/zvonimir/Programming/BlockJump/Assets/Maps/test.map", std::ios::out | std::ios::trunc | std::ios::binary};

    if (!map.SerializeToOstream(&outfile))
    {
        spdlog::error("Failed to save map!");
        return false;
    }

    spdlog::info("Map saved successfully.");
    outfile.close();

    return true;
}

std::vector<sf::RectangleShape*>& MapManager::BackgroundObjects()
{
    return background_objects_;
}

std::vector<sf::RectangleShape*>& MapManager::GetPlayerEntities()
{
    return player_entities_;
}

MapManager::~MapManager()
{
    spdlog::info("Cleaning up map data");

    for (auto drawable : background_objects_)
    {
        delete drawable;
        drawable = nullptr;
    }
}
