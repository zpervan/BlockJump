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
    header_font_ = LoadFont("KGHAPPY.ttf");
    button_font_ = LoadFont("CodeNewRoman.otf");
    click_sound_ = LoadSound("click.wav");
}

std::unique_ptr<sf::Texture> AssetsManager::LoadAsset(const std::string& asset_name)
{
    auto asset_object{std::make_unique<sf::Texture>()};

    const std::string asset_path{Paths::SpritesDirectoryPath() + asset_name};
    assert(asset_object->loadFromFile(asset_path) && "Asset doesn't exist!");

    return asset_object;
}

std::unique_ptr<sf::Font> AssetsManager::LoadFont(const std::string& font_name)
{
    auto font_object{std::make_unique<sf::Font>()};

    const std::string font_path{Paths::FontsDirectoryPath() + font_name};
    assert(font_object->loadFromFile(font_path) && "Font doesn't exist!");

    return font_object;
}

std::unique_ptr<sf::SoundBuffer> AssetsManager::LoadSound(const std::string& sound_name)
{
    auto sound_object{std::make_unique<sf::SoundBuffer>()};

    const std::string sounds_path{Paths::SoundsDirectoryPath() + sound_name};
    assert(sound_object->loadFromFile(sounds_path) && "Sound doesn't exist!");

    return sound_object;
}

sf::Texture* AssetsManager::GetTexture(AssetType type)
{
    switch (type)
    {
        case AssetType::Player:
            return player_entity_.get();
        case AssetType::DirtWithGrass:
            return background_dirt_with_grass_.get();
        case AssetType::Brick:
            return background_brick_.get();
        default:
            spdlog::error("Doesn't contain asset of that type!");
            return nullptr;
    }
}

sf::Font* AssetsManager::GetFont(FontType type)
{
    switch (type)
    {
        case FontType::Header:
            return header_font_.get();
        case FontType::Button:
            return button_font_.get();
        default:
            spdlog::error("Doesn't contain font of that type!");
            return nullptr;
    }
}

sf::SoundBuffer* AssetsManager::GetSound(SoundType type)
{
    switch (type)
    {
        case SoundType::Click:
            return click_sound_.get();
        default:
            spdlog::error("Doesn't contain sound of that type!");
            return nullptr;
    }
    return nullptr;
}
