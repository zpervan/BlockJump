#ifndef BLOCKJUMP_TILES_H
#define BLOCKJUMP_TILES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <list>

#include "MapEditor/Core/src/map_editor_events.h"

class Tiles
{
  public:
    Tiles(MapEditorEventSystem& map_editor_event_system);
    void BeginPlacement();
    void FinishPlacement();

    const std::list<sf::RectangleShape*>& GetTiles() const;
    sf::RectangleShape* GetTemporaryTile();

  private:
    MapEditorEventSystem& map_editor_event_system_;

    std::list<sf::RectangleShape*> tiles_;
    sf::RectangleShape* temporary_tile_;
};

#endif  // BLOCKJUMP_TILES_H
