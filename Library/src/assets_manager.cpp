#include "assets_manager.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <string>

#include "Library/src/paths.h"

void AssetsManager::Initialize()
{
    player_entity_ = LoadAsset("player.png");
    background_dirt_with_grass_ = LoadAsset("dirt_with_grass.png");
    background_brick_ = LoadAsset("brick.png");
}

std::unique_ptr<sf::Texture> AssetsManager::LoadAsset(const std::string& asset_name)
{
    auto asset_object{std::make_unique<sf::Texture>()};

    const std::string asset_path{Paths::SpritesDirectoryPath() + asset_name};
    assert(asset_object->loadFromFile(asset_path) && "Asset does not exist!");

    return asset_object;
}

sf::Texture* AssetsManager::Get(AssetType type)
{
    sf::Texture* texture{nullptr};

    switch (type)
    {
        case AssetType::Player:
            texture = player_entity_.get();
            break;
        case AssetType::DirtWithGrass:
            texture = background_dirt_with_grass_.get();
            break;
        case AssetType::Brick:
            texture = background_brick_.get();
            break;
        default:
            spdlog::warn("Doesn't contain asset type!");
            break;
    }

    return texture;
}
