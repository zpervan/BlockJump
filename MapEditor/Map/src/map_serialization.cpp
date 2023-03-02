#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1

#include "map_serialization.h"

#include <spdlog/spdlog.h>
/// @TODO: Use non-experimental version of filesystem
#include <filesystem>
#include <fstream>
#include <map>

#include "ProtoMessages/map/Map.pb.h"

namespace
{
std::map<AssetType, MapMessages::BackgroundTile::Type> mapped_tile_types{
    {AssetType::Brick, MapMessages::BackgroundTile::Brick},
    {AssetType::DirtWithGrass, MapMessages::BackgroundTile::DirtWithGrass}};

std::map<AssetType, std::string> mapped_tile_types_to_string{
    {AssetType::Brick, "AssetsType::Brick"},
    {AssetType::DirtWithGrass, "AssetsType::DirtWithGrass"}
};
}

/// @TODO: Allow user to choose path
constexpr auto map_file_path{"/home/zvonimir/Programming/BlockJump/Assets/Maps/test_map.map"};

bool MapSerialization::Serialize(const std::vector<std::shared_ptr<Tile>>& map_tiles)
{
    if (map_tiles.empty())
    {
        spdlog::warn("Map contains no data to save! Canceling saving process.");
        return false;
    }

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto* map = new MapMessages::Map();

    for (const auto& map_tile : map_tiles)
    {
        spdlog::debug("Adding tile of type {} on position {} {}", mapped_tile_types_to_string[map_tile->type], map_tile->shape.getPosition().x, map_tile->shape.getPosition().y);

        auto* position = new MapMessages::Position();
        position->set_x(map_tile->shape.getPosition().x);
        position->set_y(map_tile->shape.getPosition().y);

        auto* tile{map->add_background_tile()};
        tile->set_type(mapped_tile_types[map_tile->type]);
        tile->set_allocated_position(position);
    }

    std::fstream outfile{map_file_path, std::ios::out | std::ios::trunc | std::ios::binary};
    if (!map->SerializeToOstream(&outfile))
    {
        spdlog::critical("Failed to save map!");
        return false;
    }

    spdlog::info("Map saved successfully.");
    outfile.close();

    return true;
}
