#ifndef BLOCKJUMP_TILES_H
#define BLOCKJUMP_TILES_H

#include <SFML/Graphics.hpp>

#include "Library/src/assets_manager.h"
#include "ProtoMessages/map/map.pb.h"

using Tile = std::pair<sf::RectangleShape, AssetType>;

const sf::Vector2f DEFAULT_TILE_SIZE{50.0f, 50.0f};

static std::map<MapMessages::TileType, AssetType> tile_proto_to_asset_type{
    {MapMessages::TileType::TILE_TYPE_PLAYER, AssetType::Player},
    {MapMessages::TileType::TILE_TYPE_BRICK, AssetType::Brick},
    {MapMessages::TileType::TILE_TYPE_DIRT_WITH_GRASS, AssetType::DirtWithGrass},
    {MapMessages::TileType::TILE_TYPE_ICE, AssetType::Ice},
    {MapMessages::TileType::TILE_TYPE_WOODEN_BOX, AssetType::WoodenBox},
    {MapMessages::TileType::TILE_TYPE_WOODEN_BOX_BOOM, AssetType::WoodenBoxBoom},
};

static std::map<AssetType, MapMessages::TileType> tile_asset_type_to_proto{
    {AssetType::Player, MapMessages::TileType::TILE_TYPE_PLAYER},
    {AssetType::Brick, MapMessages::TileType::TILE_TYPE_BRICK},
    {AssetType::DirtWithGrass, MapMessages::TileType::TILE_TYPE_DIRT_WITH_GRASS},
    {AssetType::Ice, MapMessages::TileType::TILE_TYPE_ICE},
    {AssetType::WoodenBox, MapMessages::TileType::TILE_TYPE_WOODEN_BOX},
    {AssetType::WoodenBoxBoom, MapMessages::TileType::TILE_TYPE_WOODEN_BOX_BOOM},
};

static std::map<AssetType, std::string> tile_asset_type_to_string{
    {AssetType::Brick, "AssetsType::Brick"},
    {AssetType::DirtWithGrass, "AssetsType::DirtWithGrass"},
    {AssetType::Ice, "AssetsType::Ice"},
    {AssetType::WoodenBox, "AssetsType::WoodenBox"},
    {AssetType::WoodenBoxBoom, "AssetsType::WoodenBoxBoom"},
};

#endif  // BLOCKJUMP_TILES_H
