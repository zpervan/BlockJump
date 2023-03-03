#ifndef BLOCKJUMP_TILES_H
#define BLOCKJUMP_TILES_H

#include <SFML/Graphics.hpp>

#include "Library/src/assets_manager.h"
#include "ProtoMessages/map/Map.pb.h"

using Tile = std::pair<sf::RectangleShape, AssetType>;

static std::map<MapMessages::BackgroundTile::Type, AssetType> tile_proto_to_asset_type{
    {MapMessages::BackgroundTile::Type::BackgroundTile_Type_BRICK, AssetType::Brick},
    {MapMessages::BackgroundTile::Type::BackgroundTile_Type_DIRT_WITH_GRASS, AssetType::DirtWithGrass},
    {MapMessages::BackgroundTile::Type::BackgroundTile_Type_ICE, AssetType::Ice},
    {MapMessages::BackgroundTile::Type::BackgroundTile_Type_WOODEN_BOX, AssetType::WoodenBox},
    {MapMessages::BackgroundTile::Type::BackgroundTile_Type_WOODEN_BOX_BOOM, AssetType::WoodenBoxBoom},
};

static std::map<AssetType, MapMessages::BackgroundTile::Type> tile_asset_type_to_proto{
    {AssetType::Brick, MapMessages::BackgroundTile::Type::BackgroundTile_Type_BRICK},
    {AssetType::DirtWithGrass, MapMessages::BackgroundTile::Type::BackgroundTile_Type_DIRT_WITH_GRASS},
    {AssetType::Ice, MapMessages::BackgroundTile::Type::BackgroundTile_Type_ICE},
    {AssetType::WoodenBox, MapMessages::BackgroundTile::Type::BackgroundTile_Type_WOODEN_BOX},
    {AssetType::WoodenBoxBoom, MapMessages::BackgroundTile::Type::BackgroundTile_Type_WOODEN_BOX_BOOM},
};

static std::map<AssetType, std::string> tile_asset_type_to_string{
    {AssetType::Brick, "AssetsType::Brick"},
    {AssetType::DirtWithGrass, "AssetsType::DirtWithGrass"},
    {AssetType::Ice, "AssetsType::Ice"},
    {AssetType::WoodenBox, "AssetsType::WoodenBox"},
    {AssetType::WoodenBoxBoom, "AssetsType::WoodenBoxBoom"},
};

#endif  // BLOCKJUMP_TILES_H
