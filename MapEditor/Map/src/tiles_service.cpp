#include "tiles_service.h"

#include <spdlog/spdlog.h>

#include "MapEditor/Core/src/bootstrap.h"

TilesService::TilesService(MapEditorEventSystem& map_editor_event_system)
    : map_editor_event_system_(map_editor_event_system), temporary_tile_(nullptr)
{
}

const std::vector<std::shared_ptr<Tile>>& TilesService::GetTiles() const
{
    return tiles_;
}

std::vector<std::shared_ptr<Tile>> TilesService::CloneTiles() const
{
    return tiles_;
}

void TilesService::BeginPlacement(AssetType type)
{
    if (!temporary_tile_)
    {
        spdlog::info("Begin tile placement...");

        map_editor_event_system_.Set(MapEditorEvent::Add);

        temporary_tile_ = new Tile;
        temporary_tile_->shape.setSize({Configuration::Tile_Size, Configuration::Tile_Size});
        temporary_tile_->shape.setTexture(AssetsManager::Get(type));
        temporary_tile_->type = type;
    }
}

void TilesService::FinishPlacement()
{
    spdlog::info("Finished tile placement");

    tiles_.emplace_back(temporary_tile_);
    temporary_tile_ = nullptr;
}

Tile* TilesService::GetTemporaryTile()
{
    return temporary_tile_;
}
