#include "tiles_service.h"

#include <spdlog/spdlog.h>

#include "MapEditor/Core/src/bootstrap.h"

TilesService::TilesService(MapEditorEventSystem& map_editor_event_system)
    : map_editor_event_system_(map_editor_event_system), temporary_tile_(nullptr)
{
}

const std::list<std::unique_ptr<sf::RectangleShape>>& TilesService::GetTiles() const
{
    return tiles_;
}

void TilesService::BeginPlacement(const sf::Texture* tile_type)
{
    if(!temporary_tile_)
    {
        spdlog::info("Begin tile placement...");
        map_editor_event_system_.Set(MapEditorEvent::Add);
        temporary_tile_ = std::make_unique<sf::RectangleShape>(sf::Vector2f{Configuration::Tile_Size, Configuration::Tile_Size});
        temporary_tile_->setTexture(tile_type);
    }
}

void TilesService::FinishPlacement()
{
    spdlog::info("Finished tile placement");

    tiles_.emplace_back(std::move(temporary_tile_));
    temporary_tile_ = nullptr;
}
sf::RectangleShape* TilesService::GetTemporaryTile()
{
    return temporary_tile_.get();
}
