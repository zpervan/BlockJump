#ifndef BLOCKJUMP_TILES_SERVICE_H
#define BLOCKJUMP_TILES_SERVICE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <list>

#include "MapEditor/Core/src/map_editor_events.h"

class TilesService
{
  public:
    explicit TilesService(MapEditorEventSystem& map_editor_event_system);

    void BeginPlacement(const sf::Texture* tile_type);
    void FinishPlacement();

    const std::list<std::unique_ptr<sf::RectangleShape>>& GetTiles() const;
    sf::RectangleShape* GetTemporaryTile();

  private:
    MapEditorEventSystem& map_editor_event_system_;
    std::list<std::unique_ptr<sf::RectangleShape>> tiles_;
    std::unique_ptr<sf::RectangleShape>temporary_tile_;
};

#endif  // BLOCKJUMP_TILES_SERVICE_H
