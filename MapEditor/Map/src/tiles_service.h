#ifndef BLOCKJUMP_TILES_SERVICE_H
#define BLOCKJUMP_TILES_SERVICE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <list>
#include <memory>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_events.h"

struct Tile
{
    sf::RectangleShape shape{};
    AssetType type{AssetType::None};
};

class TilesService
{
  public:
    explicit TilesService(MapEditorEventSystem& map_editor_event_system);

    void BeginPlacement(AssetType type);
    void FinishPlacement();

    const std::vector<std::shared_ptr<Tile>>& GetTiles() const;
    std::vector<std::shared_ptr<Tile>> CloneTiles() const;
    Tile* GetTemporaryTile();

  private:
    MapEditorEventSystem& map_editor_event_system_;
    std::vector<std::shared_ptr<Tile>> tiles_;
    Tile* temporary_tile_;
};

#endif  // BLOCKJUMP_TILES_SERVICE_H
