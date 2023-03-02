#include "Library/src/map_manager.h"

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>

#include "Library/src/assets_manager.h"
#include "ProtoMessages/map/Map.pb.h"

std::map<MapMessages::BackgroundTile::Type, AssetType> tile_type{
    {MapMessages::BackgroundTile_Type::BackgroundTile_Type_Brick, AssetType::Brick},
    {MapMessages::BackgroundTile_Type::BackgroundTile_Type_DirtWithGrass, AssetType::DirtWithGrass}};

bool MapManager::Load(std::string path)
{
    spdlog::info("Loading map");

    if (!background_objects_.empty())
    {
        background_objects_.clear();
    }

    MapMessages::Map map;

    {
        // @TODO: Use the Paths functionality
        // @TODO: Check if the file exists
        std::fstream map_file{"/home/zvonimir/Programming/BlockJump/Assets/Maps/test_map.map",std::ios::in | std::ios::binary};

        if (!map.ParseFromIstream(&map_file))
        {
            spdlog::error("Failed to load map");
            return false;
        }
    }

    background_objects_.reserve(map.background_tile_size());

    for (auto& tile : map.background_tile())
    {
        auto* drawable = new sf::RectangleShape();
        drawable->setPosition(tile.position().x(), tile.position().y());
        drawable->setSize({64.0f, 64.0f});
        drawable->setTexture(AssetsManager::GetTexture(tile_type[tile.type()]));

        background_objects_.emplace_back(drawable);
    }

    spdlog::info("Map loaded successfully");

    return true;
}

std::vector<sf::RectangleShape*>& MapManager::BackgroundObjects()
{
    return background_objects_;
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
