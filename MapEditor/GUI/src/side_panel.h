#ifndef BLOCKJUMP_SIDE_PANEL_H
#define BLOCKJUMP_SIDE_PANEL_H

#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "Library/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Map/src/tiles_service.h"

class SidePanel
{
  public:
    SidePanel(TilesService& tiles_service);
    void Show();

  private:
    TilesService& tiles_service_;
    int padding_{2};
};

#endif  // BLOCKJUMP_SIDE_PANEL_H
