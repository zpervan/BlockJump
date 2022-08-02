#ifndef BLOCKJUMP_SIDE_PANEL_H
#define BLOCKJUMP_SIDE_PANEL_H

#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Map/src/tiles_service.h"

namespace
{
ImGuiWindowFlags side_panel_flags_{ImGuiWindowFlags_NoCollapse |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoFocusOnAppearing};
}

class SidePanel
{
  public:
    SidePanel(TilesService& tiles);
    void Show();

  private:
    TilesService& tiles_;
    int padding_{2};
};

#endif  // BLOCKJUMP_SIDE_PANEL_H
