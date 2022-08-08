#ifndef BLOCKJUMP_MENU_BAR_H
#define BLOCKJUMP_MENU_BAR_H

#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/Map/src/tiles_service.h"

class MenuBar
{
  public:
    MenuBar(MapEditorWindow& map_editor_window,
            TilesService& tiles_service,
            MapEditorEventSystem& map_editor_event_system);
    void Show();

  private:
    MapEditorWindow & map_editor_window_;
    MapEditorEventSystem& map_editor_event_system_;
};

#endif  // BLOCKJUMP_MENU_BAR_H
