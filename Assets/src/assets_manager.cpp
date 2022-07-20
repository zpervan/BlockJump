#include "assets_manager.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <string>

void AssetsManager::Initialize()
{
    player_entity_ = LoadAsset("player.png");
    background_dirt_ = LoadAsset("block.png");
}

std::unique_ptr<sf::Texture> AssetsManager::LoadAsset(const std::string& asset_name)
{
    auto asset_object{std::make_unique<sf::Texture>()};

    const std::string asset_path{fmt::format("Assets/sprites/{}", asset_name)};
    assert(asset_object->loadFromFile(asset_path) && fmt::format("Asset {} does not exist!", asset_name).c_str());

    return asset_object;
}

const sf::Texture* AssetsManager::GetPlayerEntity()
{
    return player_entity_.get();
}

const sf::Texture* AssetsManager::GetBackgroundDirt()
{
    return background_dirt_.get();
}
