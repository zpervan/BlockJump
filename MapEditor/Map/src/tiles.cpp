#include "tiles.h"

#include "MapEditor/Core/src/bootstrap.h"

#include <spdlog/spdlog.h>

Tiles::Tiles(MapEditorEventSystem& map_editor_event_system)
    : map_editor_event_system_(map_editor_event_system), temporary_tile_(nullptr)
{
}

const std::list<sf::RectangleShape*>& Tiles::GetTiles() const
{
    return tiles_;
}

void Tiles::BeginPlacement()
{
    if(!temporary_tile_)
    {
        spdlog::info("Begin tile placement...");
        temporary_tile_ = new sf::RectangleShape({Configuration::tile_size, Configuration::tile_size});
        temporary_tile_->setFillColor(sf::Color::Red);
    }
}

void Tiles::FinishPlacement()
{
    spdlog::info("Finished tile placement");

    tiles_.push_back(temporary_tile_);
    temporary_tile_ = nullptr;
}

sf::RectangleShape* Tiles::GetTemporaryTile()
{
    return temporary_tile_;
}
