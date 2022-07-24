#ifndef BLOCKJUMP_MENU_BAR_H
#define BLOCKJUMP_MENU_BAR_H

#include "MapEditor/Core/src/map_editor_window.h"

class MenuBar
{
  public:
    MenuBar(MapEditorWindow & map_editor_window);
    void Show();

  private:
    MapEditorWindow & map_editor_window_;
};

#endif  // BLOCKJUMP_MENU_BAR_H
