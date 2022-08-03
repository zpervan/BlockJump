#ifndef BLOCKJUMP_MENU_BAR_H
#define BLOCKJUMP_MENU_BAR_H

#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/Map/src/tiles_service.h"

class MenuBar
{
  public:
    MenuBar(MapEditorWindow& map_editor_window, TilesService& tiles_service);
    void Show();

  private:
    MapEditorWindow & map_editor_window_;
    TilesService& tiles_service_;
};

#endif  // BLOCKJUMP_MENU_BAR_H
