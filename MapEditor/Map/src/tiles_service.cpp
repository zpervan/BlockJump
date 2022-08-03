#include "tiles_service.h"

#include <spdlog/spdlog.h>

#include "MapEditor/Core/src/bootstrap.h"

TilesService::TilesService(MapEditorEventSystem& map_editor_event_system)
    : map_editor_event_system_(map_editor_event_system)
{
}

const std::list<Tile>& TilesService::GetTiles() const
{
    return tiles_;
}

void TilesService::BeginPlacement(AssetType type)
{
    if (!temporary_tile_.shape)
    {
        spdlog::info("Begin tile placement...");
        map_editor_event_system_.Set(MapEditorEvent::Add);
        temporary_tile_.shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{Configuration::Tile_Size, Configuration::Tile_Size});
        temporary_tile_.shape->setTexture(AssetsManager::Get(type));
        temporary_tile_.type = type;
    }
}

void TilesService::FinishPlacement()
{
    spdlog::info("Finished tile placement");

    tiles_.emplace_back(std::move(temporary_tile_));
    temporary_tile_.shape = nullptr;
    temporary_tile_.type = AssetType::None;
}

Tile& TilesService::GetTemporaryTile()
{
    return temporary_tile_;
}
