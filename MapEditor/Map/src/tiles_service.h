#ifndef BLOCKJUMP_TILES_SERVICE_H
#define BLOCKJUMP_TILES_SERVICE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <list>
#include <memory>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_events.h"


struct Tile
{
    std::unique_ptr<sf::RectangleShape> shape{};
    AssetType type{AssetType::None};
};

class TilesService
{
  public:
    explicit TilesService(MapEditorEventSystem& map_editor_event_system);

    void BeginPlacement(AssetType type);
    void FinishPlacement();

    const std::list<Tile>& GetTiles() const;
    Tile& GetTemporaryTile();

  private:
    MapEditorEventSystem& map_editor_event_system_;
    std::list<Tile> tiles_;
    Tile temporary_tile_;
};

#endif  // BLOCKJUMP_TILES_SERVICE_H
